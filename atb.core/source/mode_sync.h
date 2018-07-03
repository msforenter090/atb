#pragma once

// -----------------------------------------------------------------------------
// custom
// -----------------------------------------------------------------------------
#include "mode_handler.h"
#include "global_state.h"

namespace atb {
    namespace core {
        class mode_sync : public mode_handler {

        private:
            atb::core::sync_satate sync_state;

        public:
            mode_sync();

            ~mode_sync() {
            }

            bool setup() noexcept override;

            void handle() override;

            bool cleanup() noexcept override;
        };
    }
}