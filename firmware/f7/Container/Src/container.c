#include "container.h"

#include "container_template.h"
#include "fatfs.h"
#include "ff.h"
#include "mutff.h"
#include "mutff_default.h"
#include "mutff_fatfs.h"
#include <stdint.h>

#define FRAGMENT_SIZE 15

static MuTFFContext ctx;
static MuTFFMovieFile container = file_template;

static MuTFFMovieAtom *const movie = &container.movie;
static MuTFFTrackAtom *const track = &movie->track[0];
static MuTFFMediaAtom *const media = &track->media;
static MuTFFSampleTableAtom *const sample_table = &media->video_media_information.sample_table;

uint64_t duration;

MuTFFMovieDataAtom tail_mdat = {0, 0};
FSIZE_t tail_mdat_offset;

MuTFFMovieFragmentAtom moof = {
  {       // Movie fragment header
    0,      // Version
    0,      // Flags
    0,      // Sequence number
  },
  1,      // Track fragment count
  {       // Track fragments
    {       // Track fragments[0]
      {       // Track fragment header
        1,      // Track ID
        false,  // Duration is empty
        false,  // Default base is moof
        false,  // Base data offset present
        0,      // Base data offset
        false,  // Sample description index present
        0,      // Sample description index
        false,  // Default sample duration present
        0,      // Default sample duration
        false,  // Default sample size present
        0,      // Default sample size
        false,  // Default sample flags present
        0,      // Default sample flags
      },
      1,      // Track fragment run count
      {       // Track fragment runs
        {       // Track fragment runs[0]
          0,      // Version
          false,  // Data offset present
          0,      // Data offset
          false,  // First sample flags present
          0,      // First sample flags
          false,  // Sample duration present
          true,   // Sample size present
          false,  // Sample flags present
          false,  // Sample composition time offset present
          FRAGMENT_SIZE,  // Sample count
          {}      // Samples
        }
      },
      false,  // Track fragment decode time present
      {},     // Track fragment decode time
      false,  // User data present
      {}      // User data
    }
  },
  false,  // User data present
  {}      // User data
};

uint32_t sample_idx = 0;

void container_init(FIL *target_file) {
  ctx.io = mutff_fatfs_driver;
  ctx.file = target_file;

  mutff_write_movie_file(&ctx, NULL, &container);
  tail_mdat_offset = f_tell((FIL *)ctx.file);
  mutff_write_movie_data_atom(&ctx, NULL, &tail_mdat);
  f_sync(ctx.file);
}

void container_set_frame_rate(uint32_t rate) {
  container.movie.movie_header.time_scale = rate;
  container.movie.track->media.media_header.time_scale = rate;
}

void container_set_duration(uint32_t duration) {
  sample_table->time_to_sample.time_to_sample_table[0].sample_count = duration;
  sample_table->sample_to_chunk.sample_to_chunk_table[0].samples_per_chunk = duration;
  media->media_header.duration = duration;
  track->track_header.duration = duration;
  movie->movie_header.duration = duration;
  movie->movie_extends.movie_extends_header.fragment_duration = duration;
}

void container_set_resolution(uint16_t x, uint16_t y) {
  sample_table->sample_description.sample_description_table[0].data.video.width = x;
  sample_table->sample_description.sample_description_table[0].data.video.height = y;
  track->track_header.track_width = (mutff_q16_16_t) {x, 0};
  track->track_header.track_height = (mutff_q16_16_t) {y, 0};
}

void container_set_format(uint32_t format) {
  sample_table->sample_description.sample_description_table[0].data_format = format;
}

void container_set_depth(uint16_t depth) {
  sample_table->sample_description.sample_description_table[0].data.video.depth = depth;
}

///
/// @brief Handle writing data produced by the camera module to the SD card
///
/// Modifies the mdat atom (and preceding wide atom) with the new size.
/// Appends new video data to the end of the file.
/// Resets file offset to nominal position at the start of the mdat/wide atoms.
///
void container_on_dcmi_data_ready(DCMIDataReadyEventData data) {
  FRESULT err;
  unsigned int bytes_written;

  err = f_write(ctx.file, data.data, data.size, &bytes_written);
  if (err != FR_OK) {
    exit(1);
  }
  if (bytes_written != data.size) {
    // @TODO: This probably shouldn't be fatal
    exit(1);
  }

  tail_mdat.data_size += data.size;

  f_sync(ctx.file);
}

///
/// @brief Update container file metadata to add a new frame
///
/// Appends the size of the frame to the sample size table
/// Shrinks the free space atom as necessary to fit the new table entry
///
void container_on_dcmi_frame_complete(DCMIFrameCompleteEventData data) {
  moof.track_fragment->track_fragment_run[0].records[sample_idx].sample_size = data.size;
  sample_idx++;

  if (sample_idx >= FRAGMENT_SIZE) {
    FSIZE_t file_end = f_tell((FIL *) ctx.file);

    // Update duration
    // @TODO: it may be possible to avoid this
    //        supposedly duration is inferred if mehd is not present
    /* duration += FRAGMENT_SIZE; */
    /* container_set_duration(duration); */
    /* f_lseek(ctx.file, 0); */
    /* mutff_write_movie_file(&ctx, NULL, &container); */

    // Finish tailing mdat
    f_lseek(ctx.file, tail_mdat_offset);
    mutff_write_movie_data_atom(&ctx, NULL, &tail_mdat);
    f_lseek(ctx.file, file_end);
    tail_mdat.data_size = 0;

    // Write moof
    moof.movie_fragment_header.sequence_number++;
    mutff_write_movie_fragment_atom(&ctx, NULL, &moof);
    sample_idx = 0;

    tail_mdat_offset = f_tell((FIL *) ctx.file);
    mutff_write_movie_data_atom(&ctx, NULL, &tail_mdat);

    f_sync(ctx.file);
  }
}
