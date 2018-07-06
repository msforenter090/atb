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
#include "atb.common/logger.h"
#include "atb.common/message_correction_machine.h"

// -----------------------------------------------------------------------------
// PIMPL
// -----------------------------------------------------------------------------
const int client_buffer_capacity = 13;
const int client_buffer_max_fill = 12;

using namespace atb::common;
using namespace atb::network;

struct atb::network::network_client::_network_client_impl {

    atb::network::read_callback*                        read_callback;

    atb::common::ip_address_v4                          remote;

    boost::asio::ip::tcp::socket                        socket;
    char                                                data[client_buffer_capacity];
    atb::common::message_correction_machine             mcm;
    boost::asio::deadline_timer                         timer;

    _network_client_impl(
        atb::network::read_callback* read_callback,
        boost::asio::io_service& io_service,
        atb::common::ip_address_v4 remote) : read_callback(read_callback), remote(remote), socket(io_service),
        timer(io_service, boost::posix_time::seconds(1)) {
        memset(data, 0, client_buffer_capacity);

        // boost::asio::socket_base::keep_alive keep_alive_option(true);
        // socket.set_option(keep_alive_option);
    }
};

void atb::network::network_client::handle_connect(
    const boost::system::error_code& error) noexcept {

    if (error == boost::asio::error::operation_aborted)
        return;

    // -------------------------------------------------------------------------
    // No errors, connect to device.
    // -------------------------------------------------------------------------
    assert(impl != nullptr);
    raii_log_line log_line;
    if (!error) {
        format_line(log_line.ptr, "Connected to device: \"%s\"", impl->remote.ip_address);
        info(log_line.ptr);
        boost::asio::async_read(impl->socket,
                                boost::asio::buffer(impl->data, client_buffer_max_fill),
                                boost::bind(&network::network_client::handle_read, this,
                                            boost::asio::placeholders::error,
                                            boost::asio::placeholders::bytes_transferred));
    }
    else {
        format_line(log_line.ptr, "Faild to connect to device: \"%s\". Queuing for re-connect.", impl->remote.ip_address);
        info(log_line.ptr);

        impl->timer.expires_from_now(boost::posix_time::seconds(1));
        impl->timer.async_wait(boost::bind(&network_client::try_reconnect, this));
    }
}

void atb::network::network_client::handle_read(
    const boost::system::error_code& error, std::size_t bytes_transferred) {

    if (error == boost::asio::error::operation_aborted)
        return;

    if ((boost::asio::error::eof == error) ||
        (boost::asio::error::connection_reset == error) ||
        (bytes_transferred != client_buffer_max_fill)) {
        raii_log_line log_line;
        format_line(log_line.ptr, "Disconnected from device: \"%s\". Queuing for re-connect.", impl->remote.ip_address);
        info(log_line.ptr);

        impl->timer.expires_from_now(boost::posix_time::seconds(1));
        impl->timer.async_wait(boost::bind(&network_client::try_reconnect, this));
    }

    //assert(bytes_transferred == client_buffer_max_fill);
    assert(impl->read_callback != nullptr);
    post_new_message();

    memset(impl->data, 0, client_buffer_capacity);
    boost::asio::async_read(impl->socket,
                            boost::asio::buffer(impl->data, client_buffer_max_fill),
                            boost::bind(&network::network_client::handle_read, this,
                                        boost::asio::placeholders::error,
                                        boost::asio::placeholders::bytes_transferred));
}

void atb::network::network_client::try_reconnect() noexcept {
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

void atb::network::network_client::post_new_message() noexcept {
    impl->mcm.consume(impl->data, client_buffer_max_fill);
    impl->mcm.process();

    if (impl->mcm.length() > 0)
        impl->read_callback->handle(
            impl->remote, (const char*)impl->mcm.data(), impl->mcm.length()
        );
}

atb::network::network_client::network_client(atb::network::read_callback* read_callback,
                                             boost::asio::io_service& io_service, ip_address_v4& remote) noexcept {
    impl = new (std::nothrow) network_client::network_client_impl(read_callback, io_service, remote);
}

atb::network::network_client::~network_client() noexcept {
    delete impl;
    impl = nullptr;
}

bool atb::network::network_client::connect() noexcept {
    try_reconnect();
    return true;
}

bool atb::network::network_client::disconnect() noexcept {
    boost::system::error_code error;

    // -------------------------------------------------------------------------
    // https://www.boost.org/doc/libs/1_66_0/doc/html/boost_asio/reference/basic_stream_socket/close/overload2.html
    // Even if the function indicates an error, the underlying descriptor is closed.
    // 
    // This should prevent handlers from beeing after socket close.
    // -------------------------------------------------------------------------
    impl->socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both, error);
    impl->socket.close();
    return true;
}
