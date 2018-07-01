#pragma once

// -----------------------------------------------------------------------------
// std
// -----------------------------------------------------------------------------
#include <string>

// -----------------------------------------------------------------------------
// custom
// -----------------------------------------------------------------------------
#include "atb.common/ip_address_v4.h"

namespace atb {
    namespace core {

        struct zone {
        private:
            std::string z_location;
            std::string z_unknown_location;

            std::string host;
            int         port;
            int         min_rssi;
        };
    }
}