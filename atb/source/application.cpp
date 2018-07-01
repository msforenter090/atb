#include "application.h"

// -----------------------------------------------------------------------------
// custom
// -----------------------------------------------------------------------------
#include "atb.core/atb_settings_loader.h"

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

// -----------------------------------------------------------------------------
// pimpl.
// -----------------------------------------------------------------------------
struct atb::application::_app_implementation {
    // -------------------------------------------------------------------------
    // common
    // -------------------------------------------------------------------------
    message_rcv *message_receiver;

    // -------------------------------------------------------------------------
    // does atb core logic
    // -------------------------------------------------------------------------
    boost::thread_group pipeline_thread_group;
    atb::core::pipeline *pipeline;

    // -------------------------------------------------------------------------
    // network connection to remote devices
    // -------------------------------------------------------------------------
    boost::thread_group network_thread_group;
    atb::network::junction::network_junction *network_junction;

    _app_implementation() : message_receiver(nullptr), pipeline(nullptr),
        network_junction(nullptr) {
    }

    ~_app_implementation() {
        message_receiver = nullptr;
        pipeline = nullptr;
        network_junction = nullptr;
    }
};

atb::application::application() {
    implementation = new (std::nothrow) _app_implementation();
    assert(implementation != nullptr);
}

atb::application::~application() {
    delete implementation;
    implementation = nullptr;
}

void atb::application::start() {

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

    // -------------------------------------------------------------------------
    // common
    // -------------------------------------------------------------------------
    implementation->message_receiver = new (std::nothrow) message_rcv();
    assert(implementation->message_receiver != nullptr);

    // -------------------------------------------------------------------------
    // setup and start pipeline
    // -------------------------------------------------------------------------
    implementation->pipeline = new (std::nothrow)atb::core::pipeline(settings);
    assert(implementation->pipeline != nullptr);

    implementation->pipeline_thread_group.create_thread(boost::bind(
        &atb::core::pipeline::queue_worker, implementation->pipeline));
    implementation->pipeline->start();

    // -------------------------------------------------------------------------
    // setup and start network component
    // -------------------------------------------------------------------------

    char ip[] = "192.168.1.4";

    atb::network::address::ip_address_v4 add;
    memcpy(add.ip_address, ip, atb::network::address::ip_address_presentation_length);
    add.port = 10001;

    implementation->network_junction = new (std::nothrow)
        atb::network::junction::network_junction(
            implementation->message_receiver);

    assert(implementation->network_junction != nullptr);
    implementation->network_junction->remote_devices(&add, 1);

    implementation->network_thread_group.create_thread(boost::bind(
        &atb::network::junction::network_junction::queue_for_work,
        implementation->network_junction)
    );

    implementation->network_thread_group.create_thread(boost::bind(
        &atb::network::junction::network_junction::queue_for_work,
        implementation->network_junction)
    );

    implementation->network_junction->connect();
}

void atb::application::stop() {
    // -------------------------------------------------------------------------
    // stop and clean network component
    // -------------------------------------------------------------------------
    implementation->network_junction->disconnect();
    implementation->network_thread_group.join_all();
    implementation->network_junction->clean();
    delete implementation->network_junction;
    implementation->network_junction = nullptr;

    // -------------------------------------------------------------------------
    // stop and clean pipeline component
    // -------------------------------------------------------------------------
    implementation->pipeline->stop();

    // blocking
    implementation->pipeline_thread_group.join_all();
    delete implementation->pipeline;
    implementation->pipeline = nullptr;

    // -------------------------------------------------------------------------
    // common
    // -------------------------------------------------------------------------
    delete implementation->message_receiver;
    implementation->message_receiver = nullptr;
}
