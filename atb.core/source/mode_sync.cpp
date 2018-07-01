#include "mode_sync.h"

// -----------------------------------------------------------------------------
// std
// -----------------------------------------------------------------------------
#include <stdio.h>

// -----------------------------------------------------------------------------
// logger
// -----------------------------------------------------------------------------
#include "atb.common/logger.h"

void atb::core::mode_sync::handle() {
    char* log_line = atb::logger::malloc_empty_log_line();
    sprintf(log_line, "Some Work.");
    //atb::logger::info(log_line);
    atb::logger::free_log_line(log_line);
}
