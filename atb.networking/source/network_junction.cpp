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
#include "thread_safe_queue.h"
#include "network_client.h"

// -----------------------------------------------------------------------------
// PIMPL
// -----------------------------------------------------------------------------
struct atb::network::junction::network_junction::_network_junction_impl {

    atb::queue::thread_safe_queue                           queue;
    std::vector<atb::network::junction::network_client*>    clients;

    boost::asio::io_service                                 io_service;
    boost::asio::io_service::work                           work;
    boost::thread                                           dispatch_thread;

    std::unique_ptr<atb::network::address::ip_address_v4[]> remote_devices;
    unsigned int                                            remote_devices_no;

    _network_junction_impl()
        : work(io_service), dispatch_thread(
            boost::bind(&boost::asio::io_service::run, &io_service)),
        remote_devices_no(0) {
    }
};

atb::network::junction::network_junction::network_junction() noexcept
    : impl(nullptr) {
    impl = new (std::nothrow)
        atb::network::junction::network_junction::network_junction_impl();
}

atb::network::junction::network_junction::~network_junction() noexcept {

    for (auto client : impl->clients)
        delete client;

    impl->io_service.stop();
    impl->dispatch_thread.join();

    delete impl;
    impl = nullptr;
}

bool atb::network::junction::network_junction::start() noexcept {

    bool success = true;
    for (int client_count = 0;
        client_count < impl->remote_devices_no; client_count++) {

        // TODO: Handle failed to allocate memory.
        atb::network::junction::network_client* cli = new (std::nothrow)
            atb::network::junction::network_client(
                impl->io_service,
                impl->remote_devices[client_count],
                impl->queue
            );

        success &= cli->start();
        impl->clients.push_back(cli);
    }
    return success;
}

bool atb::network::junction::network_junction::stop() noexcept {

    bool success = true;
    for (auto client : impl->clients)
        success &= client->stop();
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
