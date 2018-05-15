#pragma once

// -----------------------------------------------------------------------------
// custom
// -----------------------------------------------------------------------------
#include "logger.h"

namespace atb {
    namespace network {

        const int network_message_length    = 12;
        const int internal_buffer_capacity  = 24;

        class message_correction_machine {

        private:
            typedef char    byte;

            byte            internal_buffer[internal_buffer_capacity];
            byte            out_buffer[network_message_length];

            // -----------------------------------------------------------------
            // delim is index betwean used and unused portion of the buffer.
            // delim indicates first unused buffer, on start it is zero(0).
            // out_size is indicator how much bytes are ready (decoded).
            // -----------------------------------------------------------------
            unsigned short  delim, out_size;

            inline void trim_internal_buffer_left(const unsigned int bytes) noexcept;
            inline void copy_to_output() noexcept;

        public:

            message_correction_machine() noexcept;

            // -----------------------------------------------------------------
            // <summary>
            // Appends new input to internal buffer for processing.
            // </summary>
            // -----------------------------------------------------------------
            void consume(const byte* data, unsigned int length) noexcept;

            // -----------------------------------------------------------------
            // <summary>
            // Activates machine.
            // After process returns controll data and length are updated.
            // </summary>
            // -----------------------------------------------------------------
            void process() noexcept;

            // -----------------------------------------------------------------
            // <summary>
            // Pointer to const memory block. Used to extract message from machine.
            // </summary>
            // -----------------------------------------------------------------
            const void* data() const noexcept;

            // -----------------------------------------------------------------
            // <summary>
            // Indicates how logn the message is.
            // This will always be 0 or 12.
            // Zero indicates message is not ready for copying.
            // Non zero value (12) indicates message is ready for copy.
            // </summary>
            // -----------------------------------------------------------------
            unsigned int length() const noexcept;
        };
    }
}