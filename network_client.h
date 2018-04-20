#pragma once

#include "ip_address_v4.h"
#include "thread_safe_queue.h"

#include <boost/asio.hpp>

namespace atb { 
    namespace network {
        namespace junction {

            class network_client {

            private:
                struct _network_client_impl;
                typedef _network_client_impl network_client_impl;

                network_client_impl* impl;

            public:

                network_client(boost::asio::io_service& io_service,
                    atb::network::address::ip_address_v4 remote,
                    atb::queue::thread_safe_queue& out_queue) noexcept;

                ~network_client() noexcept;

                // -------------------------------------------------------------
                // <summary>
                // Called when connection is established.
                // </summary>
                // -------------------------------------------------------------
                void handle_connect(const boost::system::error_code& code) noexcept;

                // -------------------------------------------------------------
                // <summary>
                // Private method.
                // Called when there is something to read from input stream.
                // </summary>
                // -------------------------------------------------------------
                void handle_read(const boost::system::error_code& error) noexcept;

                // -------------------------------------------------------------
                // <summary>
                // Starts listening for remote device.
                // </summary>
                // -------------------------------------------------------------
                void start() noexcept;

                // -------------------------------------------------------------
                // <summary>
                // Stops listening for remote device and closes the connection.
                // </summary>
                // -------------------------------------------------------------
                void stop() noexcept;
            };
        }
    }
}