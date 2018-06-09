#include "message_correction_machine.h"

// -----------------------------------------------------------------------------
// boost
// -----------------------------------------------------------------------------
#include <boost/regex.hpp>

// -----------------------------------------------------------------------------
// std
// -----------------------------------------------------------------------------
#include <string.h>
#include <cassert>

inline void atb::network::message_correction_machine::trim_internal_buffer_left(
    const unsigned int bytes) noexcept {
    memmove(internal_buffer,
        static_cast<char*>(internal_buffer) + bytes,
        internal_buffer_capacity - bytes);
    delim -= bytes;
}

inline void atb::network::message_correction_machine::copy_to_output() noexcept {
    memcpy(out_buffer, internal_buffer, network_message_length);
    out_size = network_message_length;
}

atb::network::message_correction_machine::message_correction_machine() noexcept
    : delim(0), out_size(0) {
    memset(internal_buffer, 0, internal_buffer_capacity);
}

void atb::network::message_correction_machine::consume(const byte* data,
    unsigned int length) noexcept {
    assert(length == network_message_length);
    assert((internal_buffer_capacity - 1) - delim >= network_message_length);

    memcpy(internal_buffer + delim, data, length);
    delim += length;
}

void atb::network::message_correction_machine::process() noexcept {

    bool matches = true;
    boost::regex message_regex("^\\[[0-9A-F]{10,10}\\]");
    std::string message;
    while (matches && delim >= network_message_length) {
        message = std::string(internal_buffer, internal_buffer + network_message_length);
        matches = boost::regex_match(message, message_regex);

        if (!matches) {
            trim_internal_buffer_left(1);
            matches = true;
            out_size = 0;
            continue;
        }

        copy_to_output();
        trim_internal_buffer_left(network_message_length);
        break;
    }
}

const void* atb::network::message_correction_machine::data() const noexcept {
    return out_buffer;
}

unsigned int atb::network::message_correction_machine::length() const noexcept {
    return out_size;
}
