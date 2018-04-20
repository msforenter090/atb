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
#include <iostream>

// -----------------------------------------------------------------------------
// custom
// -----------------------------------------------------------------------------
#include "thread_safe_queue.h"
#include "network_client.h"

// -----------------------------------------------------------------------------
// PIMPL
// -----------------------------------------------------------------------------
struct atb::network::junction::network_junction::_network_junction_impl {

    atb::queue::thread_safe_queue queue;
    std::vector<atb::network::junction::network_client*> clients;

    _network_junction_impl() {
    }

    ~_network_junction_impl() {
        
    }
};

void atb::network::junction::network_junction::handle_connect(const boost::system::error_code& code) {
    std::cout << "Callback: " << boost::this_thread::get_id() << std::endl;
    if (!code) {
        std::cout << "Success." << std::endl;
    } else {
        std::cout << "!Success." << std::endl;
    }
}

atb::network::junction::network_junction::network_junction() noexcept
    : impl(nullptr) {
    impl = new (std::nothrow)
        atb::network::junction::network_junction::network_junction_impl();

    boost::asio::io_service     io_service;
    boost::asio::io_service::work work(io_service);
    boost::thread               dispatch_thread(boost::bind(&boost::asio::io_service::run, &io_service));

    boost::asio::ip::tcp::socket socket(io_service);
    

     atb::network::address::ip_address_v4 add;
     char a[16] = "192.168.1.3\0";
     memcpy(add.ip_address, a, 16);
     add.port = 10001;

     boost::system::error_code error;
     boost::asio::ip::tcp::endpoint remote_device(
         boost::asio::ip::address_v4::from_string(add.ip_address, error),
         add.port
     );
     if (error)
         std::cout << "Error in ip address." << std::endl;

     socket.async_connect(remote_device,
         boost::bind(&network_junction::handle_connect, this,
             boost::asio::placeholders::error));

     std::cout << "Main: " << boost::this_thread::get_id() << std::endl;
     char line[100];
     while (std::cin.getline(line, 100))
     {
         using namespace std; // For strlen and memcpy.
         std::cout << line;
     }

     //dispatch_thread.join();
//     cl1->start();
//     impl->clients.push_back(cl1);
}

atb::network::junction::network_junction::~network_junction() noexcept {
//    for each (auto client in impl->clients)
//        delete client;

    delete impl;
    impl = nullptr;
}

bool atb::network::junction::network_junction::start() noexcept {

//    for each (auto client in impl->clients)
//        client->start();
    return true;
}

bool atb::network::junction::network_junction::stop() noexcept {
    return true;
}
