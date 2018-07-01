#pragma once

namespace atb {
    namespace core {
        class mode_handler {
        public:
            // -----------------------------------------------------------------
            // virtual dctor is needed, we will access mode using base class
            // -----------------------------------------------------------------
            virtual ~mode_handler() {
            };

            virtual void handle() = 0;
        };
    }
}