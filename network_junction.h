#pragma once

#include "ip_address_v4.h"

#include <boost/asio.hpp>

namespace atb {
    namespace network {
        namespace junction {
            class network_junction {

                struct _network_junction_impl;
                typedef struct _network_junction_impl network_junction_impl;

            public:
                network_junction_impl* impl;

                void handle_connect(const boost::system::error_code& code);

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
                // -------------------------------------------------------------
                // void remote_devices(
                //     atb::network::address::ip_address_v4 const * const remote,
                //     unsigned short length) noexcept;
            };
        }
    }
}