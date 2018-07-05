#pragma once

// -----------------------------------------------------------------------------
// custom
// -----------------------------------------------------------------------------
#include "atb_settings.h"
#include "atb.common/thread_safe_queue.h"

namespace atb {
    namespace core {
        class mode_handler {
        public:
            // -----------------------------------------------------------------
            // virtual dctor is needed, we will access mode using base class
            // -----------------------------------------------------------------
            virtual ~mode_handler() {
            };

            virtual bool setup(const atb::core::atb_settings& settings,
                               atb::common::thread_safe_queue* queue) noexcept = 0;

            virtual void handle() = 0;

            virtual bool cleanup() noexcept = 0;
        };
    }
}