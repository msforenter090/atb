#include <iostream>

#ifdef _WIN32
    #include <vld.h>
#endif

// -----------------------------------------------------------------------------
// Logging.
// -----------------------------------------------------------------------------
#include "spdlog/spdlog.h"

#include <iostream>

// -----------------------------------------------------------------------------
// Test network connection.
// -----------------------------------------------------------------------------
#include "network_junction.h"

#include <boost/thread.hpp>

int main(int argc, char** argv) {
    // ------------------------------------------------------------------------
    // Test spdlog on console.
    // ------------------------------------------------------------------------
    auto console = spdlog::stdout_color_mt("console");

    console->info("Welcome to spdlog!");
    console->error("Some error message with arg{}..", 1);

    char ip[] = "192.168.1.3";
    atb::network::address::ip_address_v4 add;
    memcpy(add.ip_address, ip, atb::network::address::ip_address_presentation_length);
    add.port = 10001;

    atb::network::junction::network_junction nj;

    nj.remote_devices(&add, 1);

    nj.start();

    std::cout << "Main: " << boost::this_thread::get_id() << std::endl;
    boost::this_thread::sleep_for(boost::chrono::milliseconds(10000));

    nj.stop();
    return 0;
}
