#pragma once

// -----------------------------------------------------------------------------
// boost
// -----------------------------------------------------------------------------
#include <boost/asio.hpp>

// -----------------------------------------------------------------------------
// custom
// -----------------------------------------------------------------------------
#include "read_callback.h"
#include "atb.common/logger.h"
#include "atb.common/ip_address_v4.h"

namespace atb {
    namespace network {
        namespace junction {

            class network_client {

            private:
                struct _network_client_impl;
                typedef _network_client_impl network_client_impl;

                network_client_impl* impl;

                // -------------------------------------------------------------
                // <summary>
                // Called when connection is established.
                // </summary>
                // -------------------------------------------------------------
                void handle_connect(const boost::system::error_code& code) noexcept;

                // -------------------------------------------------------------
                // <summary>
                // Called when there is something to read from input stream.
                // </summary>
                // -------------------------------------------------------------
                void handle_read(const boost::system::error_code& error) noexcept;

                // -------------------------------------------------------------
                // <summary>
                // Post new try to connect action.
                // </summary>
                // -------------------------------------------------------------
                void try_reconnect() noexcept;

            public:

                network_client(atb::logger::logger* logger,
                    atb::network::junction::read_callback* read_callback,
                    boost::asio::io_service& io_service,
                    atb::network::address::ip_address_v4& remote) noexcept;

                ~network_client() noexcept;

                // -------------------------------------------------------------
                /// <summary>
                /// Starts listening for remote device.
                /// </summary>
                // -------------------------------------------------------------
                bool start() noexcept;

                // -------------------------------------------------------------
                /// <summary>
                /// Stops listening for remote device and closes the connection.
                /// </summary>
                // -------------------------------------------------------------
                bool stop() noexcept;

                void read_callback(
                    atb::network::junction::read_callback* const read_callback) noexcept;
            };
        }
    }
}