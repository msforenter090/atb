#pragma once

namespace atb {
    namespace network {
        namespace address {

            const int ip_address_presentation_length = 16;

            struct _ip_address_v4 {

                // -------------------------------------------------------------
                // Ip address in network order.
                // -------------------------------------------------------------
                char                ip_address[ip_address_presentation_length];
                unsigned short      port;
                // -------------------------------------------------------------
                // padding is present here.
                // depending on the platform long can be 4 or 8 bytes.
                // that will make padding 2 or 6 bytes.
                // -------------------------------------------------------------
            };

            typedef struct _ip_address_v4 ip_address_v4;
        }
    }
}