#pragma once

// -----------------------------------------------------------------------------
// Defines network message from network component to pipeline.
// -----------------------------------------------------------------------------

namespace atb {
    namespace network {
        namespace message {
            const short tag_length = 6;

            struct _network_message {
                char                tag[tag_length];
                unsigned short      device_id;
                unsigned short      signal_strength;
            };

            typedef struct _network_message network_message;
        }
    }
}