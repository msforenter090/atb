#include "network_client.h"

// TODO: Make macro for switching on and off of logs.
// -----------------------------------------------------------------------------
// boost
// -----------------------------------------------------------------------------
#include <boost/thread.hpp>

// -----------------------------------------------------------------------------
// util
// -----------------------------------------------------------------------------
#include <string.h>

// -----------------------------------------------------------------------------
// logging purposes
// -----------------------------------------------------------------------------
constexpr unsigned int log_line_buffer_capacity = 1024;
char log_line_buffer[log_line_buffer_capacity];

// -----------------------------------------------------------------------------
// PIMPL
// -----------------------------------------------------------------------------
const int client_buffer_capacity = 13;
const int client_buffer_max_fill = 12;

struct atb::network::junction::network_client::_network_client_impl {

    atb::logger::logger*                                logger;
    atb::network::junction::read_callback*              read_callback;

    atb::network::address::ip_address_v4                remote;

    boost::asio::ip::tcp::socket                        socket;
    char                                                data[client_buffer_capacity];

    _network_client_impl(
        atb::logger::logger* logger,
        atb::network::junction::read_callback* read_callback,
        boost::asio::io_service& io_service,
        atb::network::address::ip_address_v4 remote)
        : logger(logger), read_callback(read_callback), remote(remote),
        socket(io_service) {
        memset(data, 0, client_buffer_capacity);
    }
};

void atb::network::junction::network_client::handle_connect(
    const boost::system::error_code& error) noexcept {

    // -------------------------------------------------------------------------
    // No errors, connect to device.
    // -------------------------------------------------------------------------
    if (!error) {
        sprintf(log_line_buffer, "Connect to device: \"%s\"", impl->remote.ip_address);
        impl->logger->info(log_line_buffer);
        boost::asio::async_read(impl->socket,
            boost::asio::buffer(impl->data, client_buffer_max_fill),
            boost::bind(&network::junction::network_client::handle_read, this,
                boost::asio::placeholders::error));
    } else {
        sprintf(log_line_buffer,
            "Faild to connect to device: \"%s\". Queuing for re-connect.",
            impl->remote.ip_address);
        impl->logger->info(log_line_buffer);
        try_reconnect();
    }
}

void atb::network::junction::network_client::handle_read(
    const boost::system::error_code& error) noexcept {

    assert(impl->read_callback != nullptr);
    impl->read_callback->handle(
        impl->remote, impl->data, client_buffer_max_fill
    );

    memset(impl->data, 0, client_buffer_capacity);
    boost::asio::async_read(impl->socket,
        boost::asio::buffer(impl->data, client_buffer_max_fill),
        boost::bind(&network::junction::network_client::handle_read, this,
            boost::asio::placeholders::error));
}

void atb::network::junction::network_client::try_reconnect() noexcept {
    // -------------------------------------------------------------------------
    // At this point ip address should be valid and no check will be performed.
    // -------------------------------------------------------------------------
    boost::asio::ip::tcp::endpoint remote_device(
        boost::asio::ip::address_v4::from_string(impl->remote.ip_address),
        impl->remote.port);

    impl->socket.async_connect(remote_device,
        boost::bind(&network_client::handle_connect, this,
            boost::asio::placeholders::error));
}

atb::network::junction::network_client::network_client(
    atb::logger::logger* logger,
    atb::network::junction::read_callback* read_callback,
    boost::asio::io_service& io_service,
    atb::network::address::ip_address_v4& remote) noexcept {
    impl = new (std::nothrow)
        atb::network::junction::network_client::network_client_impl( logger,
            read_callback, io_service, remote);
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
    boost::system::error_code error;

    // -------------------------------------------------------------------------
    // https://www.boost.org/doc/libs/1_66_0/doc/html/boost_asio/reference/basic_stream_socket/close/overload2.html
    // Even if the function indicates an error, the underlying descriptor is closed.
    // 
    // This should prevent handlers from beeing called after socket close.
    // -------------------------------------------------------------------------
    impl->socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both, error);
    impl->socket.close();
    return true;
}

void atb::network::junction::network_client::read_callback(
    atb::network::junction::read_callback* const read_callback) noexcept {
    impl->read_callback = read_callback;
}
