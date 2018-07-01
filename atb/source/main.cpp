#ifdef _WIN32
#include <vld.h>
#endif

// -----------------------------------------------------------------------------
// boost
// -----------------------------------------------------------------------------
#include <boost/thread.hpp>

// -----------------------------------------------------------------------------
// custom
// -----------------------------------------------------------------------------
#include "atb.core/atb_settings_loader.h"
#include "atb.core/pipeline.h"
#include "atb.networking/network_junction.h"

// -----------------------------------------------------------------------------
// Logging.
// -----------------------------------------------------------------------------
#include "logger_callback_implementation.h"

class message_rcv : public atb::network::junction::read_callback {
public:
    void handle(atb::network::address::ip_address_v4 address,
                void const* const data, const unsigned int length) {
        char* log_line = atb::logger::malloc_empty_log_line();
        memset(log_line, 0, 13);
        memcpy(log_line, data, length);
        atb::logger::info(log_line);
        atb::logger::free_log_line(log_line);
    }
};

int main(int argc, char** argv) {
    // -------------------------------------------------------------------------
    // Test spdlog on console.
    // -------------------------------------------------------------------------

    atb::logger::info("    ___  __________ ");
    atb::logger::info("   /   |/_  __/ __ )");
    atb::logger::info("  / /| | / / / __  |");
    atb::logger::info(" / ___ |/ / / /_/ / ");
    atb::logger::info("/_/  |_/_/ /_____/  ");
    atb::logger::info("                    ");

    atb::core::atb_settings settings;
    atb::core::atb_settings_loader settings_loader;
    settings_loader.load("", 0, settings);

    boost::thread_group thread_group;

    atb::core::pipeline pipeline(settings);
    thread_group.create_thread(boost::bind(&atb::core::pipeline::queue_worker, &pipeline));

    pipeline.start();
    boost::this_thread::sleep_for(boost::chrono::milliseconds(15000));
    pipeline.stop();

    thread_group.join_all();

    /*char ip[] = "192.168.1.4";
    message_rcv mrcv;

    atb::network::address::ip_address_v4 add;
    memcpy(add.ip_address, ip, atb::network::address::ip_address_presentation_length);
    add.port = 10001;

    atb::network::junction::network_junction nj(&mrcv);
    nj.remote_devices(&add, 1);

    boost::thread_group th;
    th.create_thread(boost::bind(
        &atb::network::junction::network_junction::queue_for_work,
        &nj)
    );

    th.create_thread(boost::bind(
        &atb::network::junction::network_junction::queue_for_work,
        &nj)
    );

    nj.connect();

    boost::this_thread::sleep_for(boost::chrono::milliseconds(90000));
    nj.disconnect();

    th.join_all();

    nj.clean();*/

#ifdef _WIN32
    system("pause");
#endif

    return 0;
}