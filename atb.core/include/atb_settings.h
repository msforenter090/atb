#pragma once

#include <string>

namespace atb {
    namespace core {

        class atb_settings {
        private:
            // -----------------------------------------------------------------
            // number of messages to receive before tag is deemed to be in the 
            // zone
            // -----------------------------------------------------------------
            unsigned short z_message_count;

            // -----------------------------------------------------------------
            // time to expire before tag is deemed to be out of the zone
            // -----------------------------------------------------------------
            unsigned long z_timeout;

        public:
            atb_settings() noexcept;

            unsigned short zone_message_count() const noexcept;

            unsigned long zone_timeout() const noexcept;

            // -----------------------------------------------------------------
            // friend declaration
            // -----------------------------------------------------------------
            friend class atb_settings_loader;
        };
    }
}