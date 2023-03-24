#ifndef EVENTS_H_
#define EVENTS_H_

#include <stdbool.h>
#include <stddef.h>

/// @brief An enum over all possible events.
typedef enum {
    /// @brief Dispatched at the end of a frame.
    DCMIFrameComplete,

    /// @brief Dispatched when some video data is valid.
    /// @note The data may only be part of a frame.
    DCMIDataReady,

    /// @brief Dispatched every time the camera produces a VSync pulse.
    ///        This should occur at the start of every frame.
    DCMIVSync,

    /// @brief Dispatched when the power button is pressed.
    PowerOff,

    /// @brief Dispatched when a cable is plugged into the USB port.
    /// @note This event is dispatched if a USB cable with only power and no data is connected.
    USBPluggedIn,
} EventType;

/// @brief An event.
typedef struct {
    /// @brief The type of the event.
    EventType type;

    /// @brief Data associated with the event.
    ///        This is cast to a DCMI*EventData type, depending on the event's type.
    void *data;
} Event;

/// @brief The data associated with a DCMIDataReady event.
typedef struct {
    /// @brief A pointer to the start of the data.
    char *data;

    /// @brief The number of valid bytes.
    size_t size;
} DCMIDataReadyEventData;

/// @brief The data associated with a DCMIFrameComplete event.
typedef struct {
    /// @brief The number of bytes in the frame.
    size_t size;
} DCMIFrameCompleteEventData;

/// @brief Adds an event to the event queue
/// @param event The event
/// @return Whether or not the event was successfully added to the queue
bool push_event_queue(Event event);

/// @brief Removes an event from the queue
/// @param event A pointer to where to store the retrieved event
/// @return Whether or not an event was removed from the queue
bool pop_event_queue(Event *event);

#endif  // EVENTS_H_
