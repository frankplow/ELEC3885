///
/// @file container.h
/// @brief Interface for ELEC3885 container file module
///
/// This file is used to manage the creation and modification
/// of a QuickTime/MP4 file.
///

#ifndef CONTAINER_H_
#define CONTAINER_H_

#include "events.h"
#include "fatfs.h"

#define MAX_FRAMES 8 * 60 * 60 * 30

void container_init(FIL *file);

void container_set_frame_rate(uint32_t rate);

void container_set_duration(uint32_t duration);

void container_set_resolution(uint16_t x, uint16_t y);

void container_set_format(uint32_t format);

void container_on_dcmi_data_ready(DCMIDataReadyEventData data);

void container_on_dcmi_frame_complete(DCMIFrameCompleteEventData data);

#endif  // CONTAINER_H_
