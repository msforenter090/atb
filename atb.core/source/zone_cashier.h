#pragma once

// -----------------------------------------------------------------------------
// custom
// -----------------------------------------------------------------------------
#include "constants.h"


// -----------------------------------------------------------------------------
// std
// -----------------------------------------------------------------------------
#include <vector>

namespace atb {
    namespace core {
        typedef struct _zone_ip_address {
            char zone_ip_address[ip_address_bytes];
        } zone_ip_address;

        // ---------------------------------------------------------------------
        // used to hold and cache zones.
        // ---------------------------------------------------------------------
        class zone_cashier {
        private:
            std::vector<zone_ip_address> cashier;

        public:
            // -----------------------------------------------------------------
            /// <summary>
            /// Makes new entry in the cache if the entry does not exists and
            /// returns it.
            /// Returns cache if the entry exists.
            /// </summary>
            // -----------------------------------------------------------------
            int cache(zone_ip_address& element);

            // -----------------------------------------------------------------
            /// <summary>
            /// Returns cached entry for the given value.
            /// If the cache does not exists calls abort.
            /// </summary>
            // -----------------------------------------------------------------
            const zone_ip_address& cache(const int cached) const;

            // -----------------------------------------------------------------
            /// <summary>
            /// Clear the cache.
            /// </summary>
            // -----------------------------------------------------------------
            void clear();
        };
    }
}