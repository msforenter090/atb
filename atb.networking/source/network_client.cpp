#include "network_client.h"

// -----------------------------------------------------------------------------
// boost
// -----------------------------------------------------------------------------
#include <boost/thread.hpp>
#include <iostream>

// -----------------------------------------------------------------------------
// PIMPL
// -----------------------------------------------------------------------------
struct atb::network::junction::network_client::_network_client_impl {
    boost::asio::io_service& io_service;
    atb::network::address::ip_address_v4 remote;
    atb::queue::thread_safe_queue& out_queue;

    boost::asio::ip::tcp::socket socket;
    _network_client_impl(boost::asio::io_service& io_service,
        atb::network::address::ip_address_v4 remote,
        atb::queue::thread_safe_queue& out_queue)
        : io_service(io_service), remote(remote), out_queue(out_queue),
            socket(io_service) {
    }
};

void atb::network::junction::network_client::handle_connect(
    const boost::system::error_code& code) noexcept {
    std::cout << "Callback: " << boost::this_thread::get_id() << std::endl;
    if (!code) {
        std::cout << "Connected to device."
            << impl->remote.ip_address << ":" << impl->remote.port << std::endl;
    }
    else {
        std::cout << "Faild to connect to device."
            << impl->remote.ip_address << ":" << impl->remote.port
            << "Re-connecting." << std::endl;
    }
}

void atb::network::junction::network_client::handle_read(
    const boost::system::error_code& error) noexcept {
}

void atb::network::junction::network_client::try_reconnect() noexcept {
    // -------------------------------------------------------------------------
    // At this point ip address should be valid and no check will be performed.
    // -------------------------------------------------------------------------
    boost::asio::ip::tcp::endpoint remote_device(
        boost::asio::ip::address_v4::from_string(impl->remote.ip_address),
        impl->remote.port
    );

    impl->socket.async_connect(remote_device,
        boost::bind(&network_client::handle_connect, this,
            boost::asio::placeholders::error));
}

atb::network::junction::network_client::network_client(
    boost::asio::io_service& io_service,
    atb::network::address::ip_address_v4& remote,
    atb::queue::thread_safe_queue& out_queue) noexcept {
    impl = new (std::nothrow)
        atb::network::junction::network_client::network_client_impl(io_service,
            remote, out_queue);
}

atb::network::junction::network_client::~network_client() noexcept {
    delete impl;
    impl = nullptr;
}

bool atb::network::junction::network_client::start() noexcept {
    try_reconnect();
    return true;
}

bool atb::network::junction::network_client::stop() noexcept {
    return true;
}
