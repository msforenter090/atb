#pragma once

// -----------------------------------------------------------------------------
// boost
// -----------------------------------------------------------------------------
#include <boost/asio.hpp>

// -----------------------------------------------------------------------------
// custom
// -----------------------------------------------------------------------------
#include "ip_address_v4.h"

namespace atb {
    namespace network {
        namespace junction {
            class network_junction {

                struct _network_junction_impl;
                typedef struct _network_junction_impl network_junction_impl;

            public:
                network_junction_impl* impl;

            public:

                // -------------------------------------------------------------
                // Creates new instance of junction.
                // -------------------------------------------------------------
                network_junction() noexcept;

                // -------------------------------------------------------------
                // Network junction dctor.
                // -------------------------------------------------------------
                ~network_junction() noexcept;

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
                /// pointer to array of ipv4 addresses to connect to.
                /// </param>
                /// <param name="length">
                /// number of ipv4 elements.
                /// </param>
                // -------------------------------------------------------------
                void remote_devices(
                     atb::network::address::ip_address_v4 const * const remote,
                     unsigned short length) noexcept;
            };
        }
    }
}