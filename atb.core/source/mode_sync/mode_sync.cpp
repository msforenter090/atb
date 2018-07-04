#include "mode_sync.h"

// -----------------------------------------------------------------------------
// std
// -----------------------------------------------------------------------------
#include <stdio.h>

// -----------------------------------------------------------------------------
// logger
// -----------------------------------------------------------------------------
#include "atb.common/logger.h"

atb::core::sync::mode_sync::mode_sync() : mode_handler() {
}

bool atb::core::sync::mode_sync::setup(const atb::core::atb_settings& settings) noexcept {
    // -------------------------------------------------------------------------
    // allocate and init memory
    // -------------------------------------------------------------------------
    return atb::core::sync::init_sync_state(settings, atb::core::max_tag_count, state);
}

void atb::core::sync::mode_sync::handle() {
    atb::common::raii_log_line log_line;
    sprintf(log_line.ptr, "Some Work.");
    atb::common::info(log_line.ptr);
}

bool atb::core::sync::mode_sync::cleanup() noexcept {
    // -------------------------------------------------------------------------
    // release and cleanup
    // -------------------------------------------------------------------------
    return atb::core::sync::destroy_sync_state(state);
}