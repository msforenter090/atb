#pragma once

// -----------------------------------------------------------------------------
// boost
// -----------------------------------------------------------------------------
#include <boost/asio.hpp>

// -----------------------------------------------------------------------------
// custom
// -----------------------------------------------------------------------------
#include "atb.common/logger.h"
#include "atb.common/ip_address_v4.h"
#include "read_callback.h"

namespace atb {
    namespace network {
        namespace junction {
            class  network_junction {

                struct _network_junction_impl;
                typedef struct _network_junction_impl network_junction_impl;

            public:
                network_junction_impl* impl;

            public:

                // -------------------------------------------------------------
                /// <summary>
                /// Creates new instance of junction.
                /// </summary>
                // -------------------------------------------------------------
                network_junction() noexcept;

                // -------------------------------------------------------------
                /// <summary>
                /// Network junction dctor.
                /// </summary>
                // -------------------------------------------------------------
                ~network_junction() noexcept;

                // -------------------------------------------------------------
                /// <summary>
                /// Registers logger callback.
                /// </summary>
                // -------------------------------------------------------------
                void register_logger_callback(
                    atb::logger::logger* const logger) noexcept;

                // -------------------------------------------------------------
                /// <summary>
                /// Registers handle read callback.
                /// </summary>
                // -------------------------------------------------------------
                void register_read_handler(
                    atb::network::junction::read_callback* const callback) noexcept;

                // -------------------------------------------------------------
                /// <summary>
                /// Connects to the remote device(s) and starts pumping messages.
                /// </summary>
                /// <returns>Returns true if start was successful.</returns>
                // -------------------------------------------------------------
                bool start() noexcept;

                // -------------------------------------------------------------
                /// <summary>
                /// Disconnectform remote devices and stops pumping messages.
                /// </summary>
                /// <returns>Returns true if stop was successful.</returns>
                // -------------------------------------------------------------
                bool stop() noexcept;

                // -------------------------------------------------------------
                /// <summary>
                /// Set devices to which to connect to.
                /// </summary>
                /// <param name="remote">
                /// Pointer to array of ipv4 addresses to connect to.
                /// </param>
                /// <param name="length">
                /// Number of ipv4 elements.
                /// </param>
                // -------------------------------------------------------------
                void remote_devices(
                     atb::network::address::ip_address_v4 const * const remote,
                     unsigned short length) noexcept;
            };
        }
    }
}