#pragma once

// -----------------------------------------------------------------------------
// std
// -----------------------------------------------------------------------------
#include <vector>

// -----------------------------------------------------------------------------
// custom
// -----------------------------------------------------------------------------
#include "zone.h"

namespace atb {
    namespace core {

        // ---------------------------------------------------------------------
        // used to hold and cache zones.
        // ---------------------------------------------------------------------
        class zone_cashier {
        private:
            std::vector<atb::core::zone> cashier;

        public:
            // -----------------------------------------------------------------
            /// <summary>
            /// Makes new entry in the cache if the entry does not exists and
            /// returns it.
            /// Returns cache if the entry exists.
            /// </summary>
            // -----------------------------------------------------------------
            int cache(atb::core::zone& element);

            // -----------------------------------------------------------------
            /// <summary>
            /// Returns cached entry for the given value.
            /// If the cache does not exists calls abort.
            /// </summary>
            // -----------------------------------------------------------------
            const atb::core::zone& cache(const int cached) const;

            // -----------------------------------------------------------------
            /// <summary>
            /// Clear the cache.
            /// </summary>
            // -----------------------------------------------------------------
            void clear();
        };
    }
}