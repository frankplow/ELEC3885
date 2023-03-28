#include "container.h"

#include "container_template.h"
#include "fatfs.h"
#include "mutff.h"
#include "mutff_fatfs.h"
#include <stdint.h>


static MuTFFMovieFile container_file = file_template;

static uint64_t size_table_length = 0;

void container_init(void) {
  mutff_set_read_fn(mutff_read_fatfs);
  mutff_set_write_fn(mutff_write_fatfs);
  mutff_set_tell_fn(mutff_tell_fatfs);
  mutff_set_seek_fn(mutff_seek_fatfs);

  mutff_write_movie_atom(&USERFile, NULL, &container_file.movie);
  mutff_write_free_atom(&USERFile, NULL, &container_file.free[0]);
  mutff_write_movie_data_atom(&USERFile, NULL, &container_file.movie_data[0]);
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
  const FSIZE_t mdat_offset = f_tell(&USERFile);

  container_file.movie_data[0].data_size += data.size;
  const uint64_t data_size = container_file.movie_data[0].data_size;

  // Reserve space for extended header if necessary
  if (data_size + 8 <= UINT32_MAX) {
    mutff_write_wide_atom(&USERFile, NULL, &(MuTFFWideAtom) {8});
  }

  mutff_write_movie_data_atom(&USERFile, NULL, &container_file.movie_data[0]);

  // Go to end of file
  err = f_lseek(&USERFile, f_size(&USERFile));
  if (err != FR_OK) {
    exit(1);
  }

  // Append data
  unsigned int bytes_written;
  err = f_write(&USERFile, data.data, data.size, &bytes_written);
  if (err != FR_OK) {
    exit(1);
  }
  if (bytes_written != data.size) {
    // @TODO: This probably shouldn't be fatal
    exit(1);
  }

  f_lseek(&USERFile, mdat_offset);
  f_sync(&USERFile);
}

void container_on_dcmi_frame_complete(DCMIFrameCompleteEventData data) {
}
