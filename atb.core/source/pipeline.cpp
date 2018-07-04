#include "pipeline.h"

// -----------------------------------------------------------------------------
// custom
// -----------------------------------------------------------------------------
#include "mode_sync/mode_sync.h"
#include "mode_wo/mode_wo.h"
#include "atb.common/logger.h"

// -----------------------------------------------------------------------------
// boost
// -----------------------------------------------------------------------------
#include "boost/asio.hpp"
#include "boost/thread.hpp"

// -----------------------------------------------------------------------------
// pimpl
// -----------------------------------------------------------------------------
struct atb::core::pipeline::_implementation {
    atb::core::atb_settings settings;
    atb::core::mode_handler* mode_h;

    // -------------------------------------------------------------------------
    // boost infrastructure
    // -------------------------------------------------------------------------
    boost::asio::io_service io_service;
    boost::asio::io_service::work work;

    _implementation(atb::core::atb_settings& settings) : settings(settings),
        mode_h(nullptr), io_service(), work(io_service) {
    }
};

atb::core::pipeline::pipeline(atb::core::atb_settings settings) {
    atb::common::raii_log_line log_line;

    // -------------------------------------------------------------------------
    // pimpl container init and log
    // -------------------------------------------------------------------------

    atb::common::format_line(log_line.ptr, atb::common::max_log_line_length,
                             "Pipeline ctor start.");
    atb::common::info(log_line.ptr);

    implementation = new (std::nothrow) _implementation(settings);
    atb::common::format_line(log_line.ptr, atb::common::max_log_line_length,
                             "Pipeline implementation: 0x: %x", implementation);
    atb::common::info(log_line.ptr);
    assert(implementation != nullptr);

    // -------------------------------------------------------------------------
    // mode handler init and log
    // -------------------------------------------------------------------------
    implementation->mode_h = new atb::core::sync::mode_sync();
    atb::common::format_line(log_line.ptr, atb::common::max_log_line_length,
                             "Pipeline mode handler: 0x: %x", implementation->mode_h);
    atb::common::info(log_line.ptr);
    assert(implementation->mode_h != nullptr);

    atb::common::format_line(log_line.ptr, atb::common::max_log_line_length,
                             "Pipeline ctor end.");
    atb::common::info(log_line.ptr);
}

atb::core::pipeline::~pipeline() {
    char* log_line = atb::common::malloc_empty_log_line();

    atb::common::format_line(log_line, atb::common::max_log_line_length,
                             "Pipeline dctor start.");
    atb::common::info(log_line);

    // -------------------------------------------------------------------------
    // cleanup in reverse order from init steps
    // clean model handler and log
    // -------------------------------------------------------------------------
    atb::common::format_line(log_line, atb::common::max_log_line_length,
                             "Pipeline mode handler: 0x: %x",
                             implementation->mode_h);
    atb::common::info(log_line);
    assert(implementation->mode_h != nullptr);
    delete implementation->mode_h;
    implementation->mode_h = nullptr;

    // -------------------------------------------------------------------------
    // mode handler clean and log
    // -------------------------------------------------------------------------
    atb::common::format_line(log_line, atb::common::max_log_line_length,
                             "Pipeline pimpl: 0x: %x", implementation);
    atb::common::info(log_line);
    assert(implementation != nullptr);
    delete implementation;
    implementation = nullptr;

    atb::common::format_line(log_line, atb::common::max_log_line_length,
                             "Pipeline dctor end.");
    atb::common::info(log_line);

    atb::common::free_log_line(log_line);
}

void atb::core::pipeline::queue_worker() {
    implementation->io_service.run();
}

void atb::core::pipeline::process_mode() {
    // -------------------------------------------------------------------------
    // processing started
    // TODO: pickup some stats
    // -------------------------------------------------------------------------
    implementation->mode_h->handle();

    // -------------------------------------------------------------------------
    // processing ended
    // TODO: pickup some stats
    // -------------------------------------------------------------------------

    boost::this_thread::sleep_for(boost::chrono::milliseconds(1000));

    // -------------------------------------------------------------------------
    // repost processing
    // -------------------------------------------------------------------------
    implementation->io_service.post(boost::bind(&atb::core::pipeline::process_mode,
                                                this));
}

bool atb::core::pipeline::start() {
    atb::common::raii_log_line log_line;

    atb::common::format_line(log_line.ptr, atb::common::max_log_line_length,
                             "Pipeline start start.");
    atb::common::info(log_line.ptr);

    // -------------------------------------------------------------------------
    // initialize mode handler before processing starts
    // -------------------------------------------------------------------------
    bool success = implementation->mode_h->setup(implementation->settings);
    if (!success) {
        atb::common::format_line(log_line.ptr, atb::common::max_log_line_length,
                                 "Pipeline mode setup failed.");
        atb::common::error(log_line.ptr);
        return false;
    }

    // -------------------------------------------------------------------------
    // post first processing loop event
    // -------------------------------------------------------------------------
    implementation->io_service.post(
        boost::bind(&atb::core::pipeline::process_mode, this));

    atb::common::format_line(log_line.ptr, atb::common::max_log_line_length,
                             "Pipeline start end.");
    atb::common::info(log_line.ptr);
}

void atb::core::pipeline::stop() {
    implementation->io_service.stop();
}

bool atb::core::pipeline::cleanup() {
    atb::common::raii_log_line log_line;

    atb::common::format_line(log_line.ptr, atb::common::max_log_line_length,
                             "Pipeline cleanup start.");
    atb::common::info(log_line.ptr);

    bool success = implementation->mode_h->cleanup();
    if (!success) {
        // ---------------------------------------------------------------------
        // should not happen, but still
        // ---------------------------------------------------------------------
        atb::common::format_line(log_line.ptr, atb::common::max_log_line_length,
                                 "Pipeline module cleanup failed.");
        atb::common::info(log_line.ptr);
        return false;
    }

    atb::common::format_line(log_line.ptr, atb::common::max_log_line_length,
                             "Pipeline cleanup end.");
    atb::common::info(log_line.ptr);
    return true;
}
