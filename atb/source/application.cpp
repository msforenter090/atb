#include "application.h"

// -----------------------------------------------------------------------------
// custom
// -----------------------------------------------------------------------------
#include "atb.common/thread_safe_queue.h"
#include "atb.core/message_parser.h"
#include "atb.core/atb_settings_loader.h"

// -----------------------------------------------------------------------------
// Logging.
// -----------------------------------------------------------------------------
#include "logger_callback.h"

using namespace atb::common;

class message_rcv : public atb::network::junction::read_callback {
private:
    atb::common::thread_safe_queue& queue;

public:
    message_rcv(atb::common::thread_safe_queue& queue) : queue(queue) {}

    void handle(atb::network::address::ip_address_v4 address,
                const char* const data, const unsigned int length) {
        atb::core::message_parser parser;
        atb::common::network_message message;
        parser.parse(data, message);

        boost::lock_guard<boost::mutex> lock_guard(queue.lock);
        queue.messages.push(message);
    }
};

// -----------------------------------------------------------------------------
// pimpl.
// -----------------------------------------------------------------------------
struct atb::application::_app_implementation {
    // -------------------------------------------------------------------------
    // common
    // -------------------------------------------------------------------------
    atb::common::thread_safe_queue queue;
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
    raii_log_line log_line;

    format_line(log_line.ptr, "<<<<<<<<<<<<<<<<<<<<< START >>>>>>>>>>>>>>>>>>>>>");
    info(log_line.ptr);

    format_line(log_line.ptr, "Application ctor start.", implementation);
    info(log_line.ptr);

    implementation = new (std::nothrow) _app_implementation();
    format_line(log_line.ptr, "Application pimpl: 0x: %x", implementation);
    info(log_line.ptr);
    assert(implementation != nullptr);

    format_line(log_line.ptr, "Application ctor end.", implementation);
    info(log_line.ptr);
}

atb::application::~application() {
    raii_log_line log_line;

    format_line(log_line.ptr, "Application dctor start.");
    info(log_line.ptr);

    format_line(log_line.ptr, "Application pimpl: 0x: %x", implementation);
    info(log_line.ptr);

    delete implementation;
    implementation = nullptr;

    format_line(log_line.ptr, "Application dctor stop.");
    info(log_line.ptr);

    format_line(log_line.ptr, "<<<<<<<<<<<<<<<<<<<<<< END >>>>>>>>>>>>>>>>>>>>>>");
    info(log_line.ptr);
}

bool atb::application::start() {
    // -------------------------------------------------------------------------
    // print app logo
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

    format_line(log_line.ptr, "ATB start start.");
    info(log_line.ptr);

    // -------------------------------------------------------------------------
    // common
    // -------------------------------------------------------------------------
    implementation->message_receiver = new (std::nothrow) message_rcv(implementation->queue);
    format_line(log_line.ptr, "Message receiver: 0x: %x", implementation->message_receiver);
    info(log_line.ptr);
    assert(implementation->message_receiver != nullptr);

    // -------------------------------------------------------------------------
    // setup and start pipeline
    // -------------------------------------------------------------------------
    implementation->pipeline = new (std::nothrow)atb::core::pipeline(settings, &(implementation->queue));
    format_line(log_line.ptr, "Application pipeline: 0x: %x", implementation->pipeline);
    info(log_line.ptr);
    assert(implementation->pipeline != nullptr);

    implementation->pipeline_thread_group.create_thread(boost::bind(&atb::core::pipeline::queue_worker, implementation->pipeline));
    format_line(log_line.ptr, "Application pipeline thread launched.");
    info(log_line.ptr);
    success = implementation->pipeline->start();
    if (!success) {
        format_line(log_line.ptr, "Application pipeline start failed.");
        info(log_line.ptr);
        return false;
    }
    format_line(log_line.ptr, "Application pipeline start success.");
    info(log_line.ptr);

    // -------------------------------------------------------------------------
    // setup and start network component
    // -------------------------------------------------------------------------

    char ip[] = "192.168.1.4";

    atb::network::address::ip_address_v4 add;
    memcpy(add.ip_address, ip, atb::network::address::ip_address_presentation_length);
    add.port = 10001;

    implementation->network_junction = new (std::nothrow) atb::network::junction::network_junction(implementation->message_receiver);
    format_line(log_line.ptr, "Application network junction: 0x: %x", implementation->network_junction);
    atb::common::info(log_line.ptr);

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
    format_line(log_line.ptr, "Application network junction started.");
    info(log_line.ptr);

    format_line(log_line.ptr, "ATB start end.");
    info(log_line.ptr);
}

void atb::application::stop() {
    raii_log_line log_line;

    format_line(log_line.ptr, "Application stop start", implementation->pipeline);
    info(log_line.ptr);

    // -------------------------------------------------------------------------
    // stop and delete network component
    // -------------------------------------------------------------------------
    format_line(log_line.ptr, "Application network junction: 0x: %x", implementation->network_junction);
    info(log_line.ptr);

    implementation->network_junction->disconnect();
    format_line(log_line.ptr, "Application network junction desiconnected.");
    info(log_line.ptr);

    implementation->network_thread_group.join_all();
    format_line(log_line.ptr, "Application network junction threads joined.");
    info(log_line.ptr);

    if (implementation != nullptr && implementation->network_junction != nullptr) {
        implementation->network_junction->clean();
        delete implementation->network_junction;
        implementation->network_junction = nullptr;
    }

    // -------------------------------------------------------------------------
    // stop and delete pipeline component
    // -------------------------------------------------------------------------
    format_line(log_line.ptr, "Application Pipeline: 0x: %x", implementation->pipeline);
    info(log_line.ptr);

    implementation->pipeline->stop();
    format_line(log_line.ptr, "Application pipeline stopped.");
    info(log_line.ptr);

    // blocking
    implementation->pipeline_thread_group.join_all();
    format_line(log_line.ptr, "Application pipeline thread joined.");
    info(log_line.ptr);

    implementation->pipeline->cleanup();
    format_line(log_line.ptr, "Application pipeline cleaned.");
    info(log_line.ptr);

    if (implementation != nullptr && implementation->pipeline) {
        delete implementation->pipeline;
        implementation->pipeline = nullptr;
    }

    // -------------------------------------------------------------------------
    // common
    // -------------------------------------------------------------------------
    format_line(log_line.ptr, "Application message receiver cleaned.");
    info(log_line.ptr);
    if (implementation != nullptr && implementation->message_receiver != nullptr) {
        delete implementation->message_receiver;
        implementation->message_receiver = nullptr;
    }

    format_line(log_line.ptr, "Application stop end", implementation->pipeline);
    atb::common::info(log_line.ptr);

    format_line(log_line.ptr, "", implementation);
    info(log_line.ptr);
}
