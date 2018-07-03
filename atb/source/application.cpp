#include "application.h"

// -----------------------------------------------------------------------------
// custom
// -----------------------------------------------------------------------------
#include "atb.core/atb_settings_loader.h"

// -----------------------------------------------------------------------------
// Logging.
// -----------------------------------------------------------------------------
#include "logger_callback.h"

class message_rcv : public atb::network::junction::read_callback {
public:
    void handle(atb::network::address::ip_address_v4 address,
                void const* const data, const unsigned int length) {
        //atb::common::raii_log_line log_line;
        //memset(log_line.ptr, 0, 13);
        //memcpy(log_line.ptr, data, length);
        // atb::common::info(log_line.ptr);
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
    atb::common::raii_log_line log_line;

    atb::common::format_line(log_line.ptr, atb::common::max_log_line_length,
                             "<<<<<<<<<<<<<<<<<<<<< START >>>>>>>>>>>>>>>>>>>>>",
                             implementation);
    atb::common::info(log_line.ptr);

    atb::common::format_line(log_line.ptr, atb::common::max_log_line_length,
                             "Application ctor start.", implementation);
    atb::common::info(log_line.ptr);

    implementation = new (std::nothrow) _app_implementation();
    atb::common::format_line(log_line.ptr, atb::common::max_log_line_length,
                             "Application pimpl: 0x: %x", implementation);
    atb::common::info(log_line.ptr);
    assert(implementation != nullptr);

    atb::common::format_line(log_line.ptr, atb::common::max_log_line_length,
                             "Application ctor end.", implementation);
    atb::common::info(log_line.ptr);
}

atb::application::~application() {
    delete implementation;
    implementation = nullptr;
}

void atb::application::start() {

    // -------------------------------------------------------------------------
    // Test spdlog on console.
    // -------------------------------------------------------------------------

    atb::common::info("    ___  __________ ");
    atb::common::info("   /   |/_  __/ __ )");
    atb::common::info("  / /| | / / / __  |");
    atb::common::info(" / ___ |/ / / /_/ / ");
    atb::common::info("/_/  |_/_/ /_____/  ");
    atb::common::info("                    ");

    atb::core::atb_settings settings;
    atb::core::atb_settings_loader settings_loader;
    settings_loader.load("", 0, settings);

    bool success = true;
    atb::common::raii_log_line log_line;
    atb::common::format_line(log_line.ptr, atb::common::max_log_line_length,
                             "ATB start start.");
    atb::common::info(log_line.ptr);
    // -------------------------------------------------------------------------
    // common
    // -------------------------------------------------------------------------
    implementation->message_receiver = new (std::nothrow) message_rcv();
    atb::common::format_line(log_line.ptr, atb::common::max_log_line_length,
                             "Message receiver: 0x: %x",
                             implementation->message_receiver);
    atb::common::info(log_line.ptr);
    assert(implementation->message_receiver != nullptr);

    // -------------------------------------------------------------------------
    // setup and start pipeline
    // -------------------------------------------------------------------------
    implementation->pipeline = new (std::nothrow)atb::core::pipeline(settings);
    atb::common::format_line(log_line.ptr, atb::common::max_log_line_length,
                             "Application pipeline: 0x: %x",
                             implementation->pipeline);
    atb::common::info(log_line.ptr);
    assert(implementation->pipeline != nullptr);

    implementation->pipeline_thread_group.create_thread(boost::bind(
        &atb::core::pipeline::queue_worker, implementation->pipeline));
    atb::common::format_line(log_line.ptr, atb::common::max_log_line_length,
                             "Application pipeline thread launched.");
    atb::common::info(log_line.ptr);
    success = implementation->pipeline->start();
    if (!success) {
        // ---------------------------------------------------------------------
        // TODO: Handle fail.
        // ---------------------------------------------------------------------
        return;
    }
    atb::common::format_line(log_line.ptr, atb::common::max_log_line_length,
                             "Application pipeline started.");
    atb::common::info(log_line.ptr);

    // -------------------------------------------------------------------------
    // setup and start network component
    // -------------------------------------------------------------------------

    /*char ip[] = "192.168.1.4";

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

    implementation->network_junction->connect();*/

    atb::common::format_line(log_line.ptr, atb::common::max_log_line_length,
                             "ATB start end.");
    atb::common::info(log_line.ptr);
}

void atb::application::stop() {
    atb::common::raii_log_line log_line;

    atb::common::format_line(log_line.ptr, atb::common::max_log_line_length,
                             "Application stop start",
                             implementation->pipeline);
    atb::common::info(log_line.ptr);
    // -------------------------------------------------------------------------
    // stop and delete network component
    // -------------------------------------------------------------------------
    /*implementation->network_junction->disconnect();
    implementation->network_thread_group.join_all();
    implementation->network_junction->clean();
    delete implementation->network_junction;
    implementation->network_junction = nullptr;*/

    // -------------------------------------------------------------------------
    // stop and delete pipeline component
    // -------------------------------------------------------------------------
    atb::common::format_line(log_line.ptr, atb::common::max_log_line_length,
                             "Application Pipeline: 0x: %x",
                             implementation->pipeline);
    atb::common::info(log_line.ptr);

    implementation->pipeline->stop();
    atb::common::format_line(log_line.ptr, atb::common::max_log_line_length,
                             "Application pipeline stopped.");
    atb::common::info(log_line.ptr);

    // blocking
    implementation->pipeline_thread_group.join_all();
    atb::common::format_line(log_line.ptr, atb::common::max_log_line_length,
                             "Application pipeline thread joined.");
    atb::common::info(log_line.ptr);

    implementation->pipeline->cleanup();
    atb::common::format_line(log_line.ptr, atb::common::max_log_line_length,
                             "Application pipeline cleaned.");
    atb::common::info(log_line.ptr);

    assert(implementation->pipeline != nullptr);
    delete implementation->pipeline;
    implementation->pipeline = nullptr;

    // -------------------------------------------------------------------------
    // common
    // -------------------------------------------------------------------------
    atb::common::format_line(log_line.ptr, atb::common::max_log_line_length,
                             "Application message receiver cleaned.");
    atb::common::info(log_line.ptr);
    assert(implementation->message_receiver);
    delete implementation->message_receiver;
    implementation->message_receiver = nullptr;

    atb::common::format_line(log_line.ptr, atb::common::max_log_line_length,
                             "Application stop end",
                             implementation->pipeline);
    atb::common::info(log_line.ptr);

    atb::common::format_line(log_line.ptr, atb::common::max_log_line_length,
                             "<<<<<<<<<<<<<<<<<<<<<< END >>>>>>>>>>>>>>>>>>>>>>",
                             implementation);
    atb::common::info(log_line.ptr);
}
