#pragma once

// -----------------------------------------------------------------------------
// custom
// -----------------------------------------------------------------------------
#include "mode_handler.h"

namespace atb {
    namespace core {
        class mode_wo : public mode_handler {

            mode_wo() : mode_handler() {
            }

            ~mode_wo() {
            }

            void handle() override;
        };
    }
}