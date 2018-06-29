#pragma once

// -----------------------------------------------------------------------------
// custom
// -----------------------------------------------------------------------------
#include "atb.common/logger.h"
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
            atb_settings* load(atb::logger::logger* const logger,
                char const * const data, const int length) noexcept;
        };
    }
}