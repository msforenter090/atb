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

using namespace atb::common;
using namespace atb::network;

struct atb::network::network_junction::_network_junction_impl {
    atb::network::read_callback*                            reader_callback;

    std::vector<atb::network::network_client*>              clients;

    boost::asio::io_service                                 io_service;
    boost::asio::io_service::work                           work;

    std::unique_ptr<atb::common::ip_address_v4[]>           remote_devices;
    unsigned int                                            remote_devices_no;

    _network_junction_impl(read_callback* const reader_callback) : reader_callback(reader_callback), work(io_service),
        remote_devices_no(0) {
    }
};

atb::network::network_junction::network_junction(read_callback* const reader_callback) noexcept : impl(nullptr) {
    impl = new (std::nothrow) atb::network::network_junction::network_junction_impl(reader_callback);
}

atb::network::network_junction::~network_junction() noexcept {
    clean();
    delete impl;
    impl = nullptr;
}

void atb::network::network_junction::queue_for_work() noexcept {
    impl->io_service.run();
}

bool atb::network::network_junction::connect() noexcept {
    bool success = true;
    impl->io_service.reset();
    for (unsigned int client_count = 0; client_count < impl->remote_devices_no; client_count++) {

        // TODO: Handle failed to allocate memory.
        atb::network::network_client* cli = new (std::nothrow) network_client(impl->reader_callback, impl->io_service,
                                                                              impl->remote_devices[client_count]
        );

        success &= cli->connect();
        impl->clients.push_back(cli);
    }
    return success;
}

bool atb::network::network_junction::disconnect() noexcept {
    bool success = true;
    for (auto client : impl->clients)
        success &= client->disconnect();
    impl->io_service.stop();
    return success;
}

bool atb::network::network_junction::clean() noexcept {
    for (auto client : impl->clients)
        delete client;
    impl->clients.clear();
    return true;
}

void atb::network::network_junction::remote_devices(atb::common::ip_address_v4 const * const remote,
                                                    unsigned short length) noexcept {
    ip_address_v4* addresses = new (std::nothrow) ip_address_v4[length];

    if (addresses == nullptr)
        return;

    std::memcpy(addresses, remote, length * sizeof(atb::common::ip_address_v4));

    impl->remote_devices.reset(addresses);
    impl->remote_devices_no = length;
}
