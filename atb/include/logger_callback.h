#pragma once

// -----------------------------------------------------------------------------
// Logging.
// -----------------------------------------------------------------------------
#include "atb.common/logger.h"
#include "logger_hub.h"

atb::logger_hub& master_logger() {
    static atb::logger_hub my_logger;
    return my_logger;
}

// -----------------------------------------------------------------------------
// Debug callback.
// -----------------------------------------------------------------------------
void atb::common::debug(const char* const message) {
    master_logger().debug(message);
}

// -----------------------------------------------------------------------------
// Info callback.
// -----------------------------------------------------------------------------
void atb::common::info(const char* const message) {
    master_logger().info(message);
}

// -----------------------------------------------------------------------------
// Warning callback.
// -----------------------------------------------------------------------------
void atb::common::warn(const char* const message) {
    master_logger().warn(message);
}

// -----------------------------------------------------------------------------
// Error callback.
// -----------------------------------------------------------------------------
void atb::common::error(const char* const message) {
    master_logger().error(message);
}

// -----------------------------------------------------------------------------
// Fatal callback.
// -----------------------------------------------------------------------------
void atb::common::fatal(const char* const message) {
    master_logger().fatal(message);
}

// -----------------------------------------------------------------------------
// Reserves log line.
// -----------------------------------------------------------------------------
char* atb::common::malloc_empty_log_line() {
    return master_logger().malloc_empty_log_line();
}

// -----------------------------------------------------------------------------
// Returns log line.
// -----------------------------------------------------------------------------
void atb::common::free_log_line(char* line) {
    master_logger().free_log_line(line);
}

// -----------------------------------------------------------------------------
// Format log line.
// -----------------------------------------------------------------------------
void atb::common::format_line(char* line, int line_capacity, char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
#ifdef _WIN32
    vsprintf_s(line, line_capacity, fmt, args);
#else
    vsprintf(line, fmt, args);
#endif
    va_end(args);
}