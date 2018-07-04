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

            enum class work_mode s_mode;

        public:
            atb_settings();

            unsigned short zone_message_count() const;

            unsigned long zone_timeout() const;

            const zone& staging() const;

            const zone& storage() const;

            const zone& decommission() const;

            const std::vector<zone> zones() const;

            int zone_number() const;

            enum class work_mode mode() const;

            // -----------------------------------------------------------------
            // friend declaration
            // -----------------------------------------------------------------
            friend class atb_settings_loader;
        };

        enum class work_mode {
            SYNC, WORK_ORDER
        };
    }
}