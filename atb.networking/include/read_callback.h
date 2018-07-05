#pragma once

#include "atb.common/ip_address_v4.h"

namespace atb {
    namespace network {
        namespace junction {
            class read_callback {

            public:
                // -------------------------------------------------------------
                /// <summary>
                /// Called when new data has been received from the network.
                /// </summary>
                /// <param name="address">Address and port traffic occurred.</param>
                /// <param name="data">New data.</param>
                /// <param name="length">Length of data (in bytes).</param>
                // -------------------------------------------------------------
                virtual void handle(atb::network::address::ip_address_v4 address,
                                    char const* const data, const unsigned int length) = 0;
            };
        }
    }
}