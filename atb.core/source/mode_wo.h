#pragma once

// -----------------------------------------------------------------------------
// custom
// -----------------------------------------------------------------------------
#include "mode_handler.h"
#include "global_state.h"

namespace atb {
    namespace core {
        class mode_wo : public mode_handler {

        private:
            atb::core::wo_satate wo_state;

        public:
            mode_wo() : mode_handler() {
            }

            ~mode_wo() {
            }

            bool setup() noexcept override;

            void handle() override;

            bool cleanup() noexcept override;
        };
    }
}