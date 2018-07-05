#include "message_parser.h"

// -----------------------------------------------------------------------------
// std
// -----------------------------------------------------------------------------
#include <string.h>
#include <string>

bool atb::core::message_parser::parse(const char* const data,
                                      atb::common::network_message& msg) {
    char dev_id_str[3];
    char sig_strength_str[3];

    memset(dev_id_str, 0, 3);
    memset(sig_strength_str, 0, 3);

    memcpy(sig_strength_str, data + 1, 2);
    memcpy(msg.tag, data + 3, 9);
    memcpy(dev_id_str, data + 9, 2);

    int sig_strength = static_cast<int>(strtol(sig_strength_str, nullptr, 16));
    int dev_id = static_cast<int>(strtol(dev_id_str, nullptr, 16));
    msg.signal_strength = sig_strength;
    msg.device_id = dev_id;
    return true;
}
