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

void container_init(void);

void container_on_dcmi_data_ready(DCMIDataReadyEventData data);

void container_on_dcmi_frame_complete(DCMIFrameCompleteEventData data);

#endif  // CONTAINER_H_
