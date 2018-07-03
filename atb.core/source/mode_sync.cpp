#include "mode_sync.h"

// -----------------------------------------------------------------------------
// std
// -----------------------------------------------------------------------------
#include <stdio.h>

// -----------------------------------------------------------------------------
// logger
// -----------------------------------------------------------------------------
#include "atb.common/logger.h"

atb::core::mode_sync::mode_sync() : mode_handler() {
}

bool atb::core::mode_sync::setup() noexcept {
    return true;
}

void atb::core::mode_sync::handle() {
    atb::common::raii_log_line log_line;
    //sprintf(log_line.ptr, "Some Work.");
    //atb::common::info(log_line.ptr);
}

bool atb::core::mode_sync::cleanup() noexcept {
    return true;
}