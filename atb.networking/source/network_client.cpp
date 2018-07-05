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

struct atb::network::junction::network_client::_network_client_impl {

    atb::network::junction::read_callback*              read_callback;

    atb::network::address::ip_address_v4                remote;

    boost::asio::ip::tcp::socket                        socket;
    char                                                data[client_buffer_capacity];
    atb::network::message_correction_machine            mcm;
    boost::asio::deadline_timer                         timer;

    _network_client_impl(
        atb::network::junction::read_callback* read_callback,
        boost::asio::io_service& io_service,
        atb::network::address::ip_address_v4 remote)
        : read_callback(read_callback), remote(remote), socket(io_service),
        timer(io_service, boost::posix_time::seconds(1)) {
        memset(data, 0, client_buffer_capacity);

        // boost::asio::socket_base::keep_alive keep_alive_option(true);
        // socket.set_option(keep_alive_option);
    }
};

void atb::network::junction::network_client::handle_connect(
    const boost::system::error_code& error) noexcept {

    if (error == boost::asio::error::operation_aborted)
        return;

    // -------------------------------------------------------------------------
    // No errors, connect to device.
    // -------------------------------------------------------------------------
    assert(impl != nullptr);
    if (!error) {
        char* log_line_buffer = atb::common::malloc_empty_log_line();
        sprintf(log_line_buffer, "Connected to device: \"%s\"",
                impl->remote.ip_address);
        atb::common::info(log_line_buffer);
        atb::common::free_log_line(log_line_buffer);
        boost::asio::async_read(impl->socket,
                                boost::asio::buffer(impl->data, client_buffer_max_fill),
                                boost::bind(&network::junction::network_client::handle_read, this,
                                            boost::asio::placeholders::error,
                                            boost::asio::placeholders::bytes_transferred));
    }
    else {
        char* log_line_buffer = atb::common::malloc_empty_log_line();
        sprintf(log_line_buffer,
                "Faild to connect to device: \"%s\". Queuing for re-connect.",
                impl->remote.ip_address);
        atb::common::info(log_line_buffer);
        atb::common::free_log_line(log_line_buffer);

        impl->timer.expires_from_now(boost::posix_time::seconds(1));
        impl->timer.async_wait(boost::bind(&network_client::try_reconnect, this));
    }
}

void atb::network::junction::network_client::handle_read(
    const boost::system::error_code& error, std::size_t bytes_transferred) {

    if (error == boost::asio::error::operation_aborted)
        return;

    if ((boost::asio::error::eof == error) ||
        (boost::asio::error::connection_reset == error) ||
        (bytes_transferred != client_buffer_max_fill)) {
        char* log_line_buffer = atb::common::malloc_empty_log_line();
        sprintf(log_line_buffer,
                "Disconnected from device: \"%s\". Queuing for re-connect.",
                impl->remote.ip_address);
        atb::common::info(log_line_buffer);
        atb::common::free_log_line(log_line_buffer);

        impl->timer.expires_from_now(boost::posix_time::seconds(1));
        impl->timer.async_wait(boost::bind(&network_client::try_reconnect, this));
    }

    //assert(bytes_transferred == client_buffer_max_fill);
    assert(impl->read_callback != nullptr);
    post_new_message();

    memset(impl->data, 0, client_buffer_capacity);
    boost::asio::async_read(impl->socket,
                            boost::asio::buffer(impl->data, client_buffer_max_fill),
                            boost::bind(&network::junction::network_client::handle_read, this,
                                        boost::asio::placeholders::error,
                                        boost::asio::placeholders::bytes_transferred));
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

void atb::network::junction::network_client::post_new_message() noexcept {
    impl->mcm.consume(impl->data, client_buffer_max_fill);
    impl->mcm.process();

    if (impl->mcm.length() > 0)
        impl->read_callback->handle(
            impl->remote, (const char*)impl->mcm.data(), impl->mcm.length()
        );
}

atb::network::junction::network_client::network_client(
    atb::network::junction::read_callback* read_callback,
    boost::asio::io_service& io_service,
    atb::network::address::ip_address_v4& remote) noexcept {
    impl = new (std::nothrow)
        atb::network::junction::network_client::network_client_impl(read_callback, io_service, remote);
}

atb::network::junction::network_client::~network_client() noexcept {
    delete impl;
    impl = nullptr;
}

bool atb::network::junction::network_client::connect() noexcept {
    try_reconnect();
    return true;
}

bool atb::network::junction::network_client::disconnect() noexcept {
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
