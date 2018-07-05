#pragma once

// -----------------------------------------------------------------------------
// custom
// -----------------------------------------------------------------------------
#include "atb.common/network_message.h"

namespace atb {
    namespace core {
        class message_parser {
        public:
            bool parse(const char* const data, atb::common::network_message& msg);
        };
    }
}