#include "container.h"

#include "container_template.h"
#include "fatfs.h"
#include "mutff.h"
#include "mutff_fatfs.h"
#include <stdint.h>

static FIL *file;

static MuTFFMovieFile container = file_template;

static MuTFFMovieAtom *const movie = &container.movie;
static MuTFFTrackAtom *const track = &movie->track[0];
static MuTFFMediaAtom *const media = &track->media;
static MuTFFSampleTableAtom *const sample_table = &media->video_media_information.sample_table;

void container_init(FIL *target_file) {
  file = target_file;
  mutff_set_read_fn(mutff_read_fatfs);
  mutff_set_write_fn(mutff_write_fatfs);
  mutff_set_tell_fn(mutff_tell_fatfs);
  mutff_set_seek_fn(mutff_seek_fatfs);

  mutff_write_movie_atom(file, NULL, &container.movie);
  mutff_write_free_atom(file, NULL, &container.free[0]);
  mutff_write_movie_data_atom(file, NULL, &container.movie_data[0]);
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

///
/// @brief Handle writing data produced by the camera module to the SD card
///
/// Modifies the mdat atom (and preceding wide atom) with the new size.
/// Appends new video data to the end of the file.
/// Resets file offset to nominal position at the start of the mdat/wide atoms.
///
void container_on_dcmi_data_ready(DCMIDataReadyEventData data) {
  FRESULT err;
  const FSIZE_t mdat_offset = f_tell(file);

  container.movie_data[0].data_size += data.size;
  const uint64_t data_size = container.movie_data[0].data_size;

  // Reserve space for extended header if necessary
  if (data_size + 8 <= UINT32_MAX) {
    mutff_write_wide_atom(file, NULL, &(MuTFFWideAtom) {8});
  }

  mutff_write_movie_data_atom(file, NULL, &container.movie_data[0]);

  // Go to end of file
  err = f_lseek(file, f_size(file));
  if (err != FR_OK) {
    exit(1);
  }

  // Append data
  unsigned int bytes_written;
  err = f_write(file, data.data, data.size, &bytes_written);
  if (err != FR_OK) {
    exit(1);
  }
  if (bytes_written != data.size) {
    // @TODO: This probably shouldn't be fatal
    exit(1);
  }

  f_lseek(file, mdat_offset);
  f_sync(file);
}

void container_on_dcmi_frame_complete(DCMIFrameCompleteEventData data) {
}
