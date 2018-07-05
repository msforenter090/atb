#pragma once

// -----------------------------------------------------------------------------
// custom
// -----------------------------------------------------------------------------
#include "mode_handler.h"
#include "mode_sync/sync_state.h"

namespace atb {
    namespace core {
        namespace sync {
            class mode_sync : public mode_handler {

            private:
                atb::core::sync::sync_state state;

            public:
                mode_sync();

                ~mode_sync() {
                }

                bool setup(const atb::core::atb_settings& settings,
                           atb::common::thread_safe_queue* queue) noexcept override;

                void handle() override;

                bool cleanup() noexcept override;
            };
        }
    }
}