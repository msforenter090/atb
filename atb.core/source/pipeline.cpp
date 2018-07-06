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

using namespace atb::common;
using namespace atb::core;

struct atb::core::pipeline::_implementation {
    atb_settings settings;
    mode_handler* mode_h;
    thread_safe_queue* queue;

    // -------------------------------------------------------------------------
    // boost infrastructure
    // -------------------------------------------------------------------------
    boost::asio::io_service io_service;
    boost::asio::io_service::work work;

    _implementation(atb_settings& settings, thread_safe_queue* queue)
        : settings(settings), mode_h(nullptr), queue(queue), io_service(),
        work(io_service) {
    }
};

atb::core::pipeline::pipeline(atb::core::atb_settings settings,
                              atb::common::thread_safe_queue* queue) {
    raii_log_line log_line;

    // -------------------------------------------------------------------------
    // pimpl container init and log
    // -------------------------------------------------------------------------

    format_line(log_line.ptr, "Pipeline ctor start.");
    info(log_line.ptr);

    implementation = new (std::nothrow) _implementation(settings, queue);
    format_line(log_line.ptr, "Pipeline implementation: 0x: %x", implementation);
    info(log_line.ptr);
    assert(implementation != nullptr);

    // -------------------------------------------------------------------------
    // mode handler init and log
    // -------------------------------------------------------------------------
    implementation->mode_h = new atb::core::sync::mode_sync();
    format_line(log_line.ptr, "Pipeline mode handler: 0x: %x", implementation->mode_h);
    info(log_line.ptr);
    assert(implementation->mode_h != nullptr);

    format_line(log_line.ptr, "Pipeline ctor end.");
    info(log_line.ptr);
}

atb::core::pipeline::~pipeline() {
    raii_log_line log_line;

    format_line(log_line.ptr, "Pipeline dctor start.");
    info(log_line.ptr);

    // -------------------------------------------------------------------------
    // cleanup in reverse order from init steps
    // clean model handler and log
    // -------------------------------------------------------------------------
    format_line(log_line.ptr, "Pipeline mode handler: 0x: %x", implementation->mode_h);
    info(log_line.ptr);
    assert(implementation->mode_h != nullptr);
    delete implementation->mode_h;
    implementation->mode_h = nullptr;

    // -------------------------------------------------------------------------
    // mode handler clean and log
    // -------------------------------------------------------------------------
    format_line(log_line.ptr, "Pipeline pimpl: 0x: %x", implementation);
    info(log_line.ptr);
    assert(implementation != nullptr);
    delete implementation;
    implementation = nullptr;

    format_line(log_line.ptr, "Pipeline dctor end.");
    info(log_line.ptr);
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
    raii_log_line log_line;

    format_line(log_line.ptr, "Pipeline start start.");
    info(log_line.ptr);

    // -------------------------------------------------------------------------
    // initialize mode handler before processing starts
    // -------------------------------------------------------------------------
    bool success = implementation->mode_h->setup(implementation->settings,
                                                 implementation->queue);
    if (!success) {
        format_line(log_line.ptr, "Pipeline mode setup failed.");
        error(log_line.ptr);
        return false;
    }

    // -------------------------------------------------------------------------
    // post first processing loop event
    // -------------------------------------------------------------------------
    implementation->io_service.post(
        boost::bind(&atb::core::pipeline::process_mode, this));

    format_line(log_line.ptr, "Pipeline start end.");
    info(log_line.ptr);
    return true;
}

void atb::core::pipeline::stop() {
    implementation->io_service.stop();
}

bool atb::core::pipeline::cleanup() {
    raii_log_line log_line;

    format_line(log_line.ptr, "Pipeline cleanup start.");
    info(log_line.ptr);

    bool success = implementation->mode_h->cleanup();
    if (!success) {
        // ---------------------------------------------------------------------
        // should not happen, but still
        // ---------------------------------------------------------------------
        format_line(log_line.ptr, "Pipeline module cleanup failed.");
        info(log_line.ptr);
        return false;
    }

    format_line(log_line.ptr, "Pipeline cleanup end.");
    info(log_line.ptr);
    return true;
}
