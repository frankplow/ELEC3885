#include "container.h"

#include "container_template.h"
#include "fatfs.h"
#include "ff.h"
#include "mutff.h"
#include "mutff_default.h"
#include "mutff_fatfs.h"
#include <stdint.h>

#define FRAGMENT_SIZE 16

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
  .movie_fragment_header = {
    .version = 0,
    .flags = 0,
    .sequence_number = 0,
  },
  .track_fragment_count = 1,
  .track_fragment = {
    {
      .track_fragment_header = {
        .track_id = 1,
        .duration_is_empty = false,
        .default_base_is_moof = false,
        .base_data_offset_present = true,
        .sample_description_index_present = false,
        .default_sample_duration_present = false,
        .default_sample_size_present = false,
        .default_sample_flags_present = false,
      },
      .track_fragment_run_count = 1,
      .track_fragment_run = {
        {
          .version = 0,
          .data_offset_present = false,
          .first_sample_flags_present = false,
          .sample_duration_present = false,
          .sample_size_present = true,
          .sample_flags_present = false,
          .sample_composition_time_offset_present = false,
          .sample_count = FRAGMENT_SIZE,
        }
      },
      .track_fragment_decode_time_present = false,
      .user_data_present = false,
    }
  },
  .user_data_present = false,
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

    // Finish tailing mdat
    f_lseek(ctx.file, tail_mdat_offset);
    mutff_write_movie_data_atom(&ctx, NULL, &tail_mdat);
    f_lseek(ctx.file, file_end);
    tail_mdat.data_size = 0;

    // Write moof
    moof.movie_fragment_header.sequence_number++;
    moof.track_fragment->track_fragment_header.base_data_offset = tail_mdat_offset;
    mutff_write_movie_fragment_atom(&ctx, NULL, &moof);
    sample_idx = 0;

    // Start next mdat
    tail_mdat_offset = f_tell((FIL *) ctx.file);
    mutff_write_movie_data_atom(&ctx, NULL, &tail_mdat);

    f_sync(ctx.file);
  }
}
