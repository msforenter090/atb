#include "network_junction.h"

// -----------------------------------------------------------------------------
// useful
// https://stackoverflow.com/questions/1942550/dedicated-thread-for-io-servicerun
//
// pay attention to work object
// https://www.boost.org/doc/libs/1_45_0/doc/html/boost_asio/example/services/logger_service.hpp
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// std
// -----------------------------------------------------------------------------
#include <vector>

// -----------------------------------------------------------------------------
// boost
// -----------------------------------------------------------------------------
#include <boost/thread.hpp>

// -----------------------------------------------------------------------------
// custom
// -----------------------------------------------------------------------------
#include "network_client.h"

// -----------------------------------------------------------------------------
// PIMPL
// -----------------------------------------------------------------------------
struct atb::network::junction::network_junction::_network_junction_impl {

    atb::logger::logger*                                    logger_callback;
    atb::network::junction::read_callback*                  reader_callback;

    std::vector<atb::network::junction::network_client*>    clients;

    boost::asio::io_service                                 io_service;
    boost::asio::io_service::work                           work;

    std::unique_ptr<atb::network::address::ip_address_v4[]> remote_devices;
    unsigned int                                            remote_devices_no;

    _network_junction_impl(
        atb::logger::logger* const logger_callback,
        atb::network::junction::read_callback* const reader_callback)
        : logger_callback(logger_callback), reader_callback(reader_callback),
            work(io_service), remote_devices_no(0) {
    }
};

atb::network::junction::network_junction::network_junction(
    atb::logger::logger* const logger_callback,
    atb::network::junction::read_callback* const reader_callback) noexcept
    : impl(nullptr) {
    impl = new (std::nothrow)
        atb::network::junction::network_junction::network_junction_impl(
            logger_callback, reader_callback);
}

atb::network::junction::network_junction::~network_junction() noexcept {
    delete impl;
    impl = nullptr;
}

void atb::network::junction::network_junction::queue_for_work() noexcept {
    impl->io_service.run();
}

bool atb::network::junction::network_junction::connect() noexcept {
    bool success = true;
    impl->io_service.reset();
    for (unsigned int client_count = 0;
        client_count < impl->remote_devices_no; client_count++) {

        // TODO: Handle failed to allocate memory.
        atb::network::junction::network_client* cli = new (std::nothrow)
            atb::network::junction::network_client(impl->logger_callback,
                impl->reader_callback, impl->io_service,
                impl->remote_devices[client_count]
            );

        success &= cli->connect();
        impl->clients.push_back(cli);
    }
    return success;
}

bool atb::network::junction::network_junction::disconnect() noexcept {
    bool success = true;
    for (auto client : impl->clients) {
        success &= client->disconnect();
        delete client;
    }
    impl->io_service.stop();
    return success;
}

void atb::network::junction::network_junction::remote_devices(
    atb::network::address::ip_address_v4 const * const remote,
    unsigned short length) noexcept {
    atb::network::address::ip_address_v4* addresses =
        new (std::nothrow) atb::network::address::ip_address_v4[length];

    if (addresses == nullptr)
        return;

    std::memcpy(addresses, remote,
        length * sizeof(atb::network::address::ip_address_v4));

    impl->remote_devices.reset(addresses);
    impl->remote_devices_no = length;
}
