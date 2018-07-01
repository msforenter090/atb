#pragma once

// -----------------------------------------------------------------------------
// std
// -----------------------------------------------------------------------------
#include <string>
#include <vector>

// -----------------------------------------------------------------------------
// custom
// -----------------------------------------------------------------------------
#include "zone.h"

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

            // -----------------------------------------------------------------
            // must have locations, these are manadatory, can be invalid
            // but they are must have (system zones)
            // -----------------------------------------------------------------
            zone z_staging;

            zone z_storage;

            zone z_decommission;

            // -----------------------------------------------------------------
            // all zones
            // -----------------------------------------------------------------
            std::vector<zone> all_zones;

        public:
            atb_settings() noexcept;

            unsigned short zone_message_count() const noexcept;

            unsigned long zone_timeout() const noexcept;

            const zone& staging() const noexcept;

            const zone& storage() const noexcept;

            const zone& decommission() const noexcept;

            int zone_number() const noexcept;

            // -----------------------------------------------------------------
            // friend declaration
            // -----------------------------------------------------------------
            friend class atb_settings_loader;
        };
    }
}