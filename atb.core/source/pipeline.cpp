#include "pipeline.h"

// -----------------------------------------------------------------------------
// custom
// -----------------------------------------------------------------------------
#include "mode_sync.h"

// -----------------------------------------------------------------------------
// pimpl
// -----------------------------------------------------------------------------
struct atb::core::pipeline::_implementation {
    atb::core::atb_settings settings;
    atb::core::mode_handler* mode;

    // -------------------------------------------------------------------------
    // boost infrastructure
    // -------------------------------------------------------------------------
    boost::asio::io_service io_service;
    boost::asio::io_service::work work;

    _implementation(atb::core::atb_settings& settings) : settings(settings),
        mode(new mode_sync()), io_service(), work(io_service) {
    }

    ~_implementation() {
        delete mode;
        mode = nullptr;
    }
};

atb::core::pipeline::pipeline(atb::core::atb_settings settings) {
    implementation = new _implementation(settings);
    assert(implementation != nullptr);
}

atb::core::pipeline::~pipeline() {
    delete implementation;
    implementation = nullptr;
}

void atb::core::pipeline::queue_worker() noexcept {
    implementation->io_service.run();
}

void atb::core::pipeline::process_mode() {
    // -------------------------------------------------------------------------
    // processing started
    // TODO: pickup some stats
    // -------------------------------------------------------------------------
    implementation->mode->handle();

    // -------------------------------------------------------------------------
    // processing ended
    // TODO: pickup some stats
    // -------------------------------------------------------------------------

    boost::this_thread::sleep_for(boost::chrono::milliseconds(60));
    // -------------------------------------------------------------------------
    // repost processing
    // -------------------------------------------------------------------------
    implementation->io_service.post(boost::bind(&atb::core::pipeline::process_mode,
                                                this));
}

void atb::core::pipeline::start() {
    // -------------------------------------------------------------------------
    // post processing loop
    // -------------------------------------------------------------------------
    implementation->io_service.post(boost::bind(&atb::core::pipeline::process_mode,
                                                this));
}

void atb::core::pipeline::stop() {
    implementation->io_service.stop();
}
