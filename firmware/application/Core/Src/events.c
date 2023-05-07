#include "events.h"

#include <stddef.h>

/// @brief The maximum number of events in the queue at a given time
#define MAX_PENDING_EVENTS 8

/// @brief The number of events in the queue.
static size_t pending_events = 0;

/// @brief An array of events which are waiting to be dispatched.
///        The first element is the oldest.
static Event event_queue[MAX_PENDING_EVENTS];

bool push_event_queue(Event event) {
    if (pending_events >= MAX_PENDING_EVENTS) {
        return false;
    }

    event_queue[pending_events] = event;
    pending_events++;
    return true;
}

bool pop_event_queue(Event *event) {
    if (pending_events == 0) {
        return false;
    }

    *event = event_queue[0];

    pending_events--;
    for (size_t i = 0; i < pending_events; ++i) {
        event_queue[i] = event_queue[i + 1];
    }

    return true;
}
