#pragma once

// -----------------------------------------------------------------------------
// custom
// -----------------------------------------------------------------------------
#include "mode_handler.h"
#include "mode_wo/wo_state.h"

namespace atb {
    namespace core {
        class mode_wo : public mode_handler {

        private:
            atb::core::wo::wo_satate wo_state;

        public:
            mode_wo() : mode_handler() {
            }

            ~mode_wo() {
            }

            bool setup(const atb::core::atb_settings& settings) noexcept override;

            void handle() override;

            bool cleanup() noexcept override;
        };
    }
}