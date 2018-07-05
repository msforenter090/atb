#pragma once

// -----------------------------------------------------------------------------
// std
// -----------------------------------------------------------------------------
#include <cassert>

// -----------------------------------------------------------------------------
// custom
// -----------------------------------------------------------------------------
#include "global_state.h"
#include "atb.common/thread_safe_queue.h"

namespace atb {
    namespace core {
        namespace sync {
            // -----------------------------------------------------------------
            // SYNC state
            // -----------------------------------------------------------------
            typedef struct _sync_state {
                atb_settings settings;
                atb::common::thread_safe_queue* queue;
                tag_detection_state detection_satate;
            } sync_state;

            bool init_sync_state(const atb::core::atb_settings& settings,
                                 int max_tag_number,
                                 atb::common::thread_safe_queue* queue,
                                 atb::core::sync::sync_state& state);

            bool destroy_sync_state(atb::core::sync::sync_state& state);
        }
    }
}