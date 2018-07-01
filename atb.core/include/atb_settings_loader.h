#pragma once

// -----------------------------------------------------------------------------
// custom
// -----------------------------------------------------------------------------
#include "atb_settings.h"

namespace atb {
    namespace core {

        class atb_settings_loader {
        public:
            // -----------------------------------------------------------------
            /// <summary>
            /// Load atb setting from passed in string configuration.
            /// If load fails for any reason nullptr is returned.
            /// </summary>
            // -----------------------------------------------------------------
            bool load(char const* const data, const int length,
                      atb_settings& settings) noexcept;
        };
    }
}