#pragma once

// -----------------------------------------------------------------------------
// custom
// -----------------------------------------------------------------------------
#include "mode_handler.h"

namespace atb {
    namespace core {
        class mode_sync : public mode_handler {

        public:
            mode_sync() : mode_handler() {
            }

            ~mode_sync() {
            }

            void handle() override;
        };
    }
}