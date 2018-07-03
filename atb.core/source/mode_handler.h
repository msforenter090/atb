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

            virtual bool setup() noexcept = 0;

            virtual void handle() = 0;

            virtual bool cleanup() noexcept = 0;
        };
    }
}