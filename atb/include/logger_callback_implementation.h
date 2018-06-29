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
void atb::logger::debug(const char* const message) noexcept {
    master_logger().debug(message);
}

// -----------------------------------------------------------------------------
// Info callback.
// -----------------------------------------------------------------------------
void atb::logger::info(const char* const message) noexcept {
    master_logger().info(message);
}

// -----------------------------------------------------------------------------
// Warning callback.
// -----------------------------------------------------------------------------
void atb::logger::warn(const char* const message) noexcept {
    master_logger().warn(message);
}

// -----------------------------------------------------------------------------
// Error callback.
// -----------------------------------------------------------------------------
void atb::logger::error(const char* const message) noexcept {
    master_logger().error(message);
}

// -----------------------------------------------------------------------------
// Fatal callback.
// -----------------------------------------------------------------------------
void atb::logger::fatal(const char* const message) noexcept {
    master_logger().fatal(message);
}

// -----------------------------------------------------------------------------
// Reserves log line.
// -----------------------------------------------------------------------------
char* atb::logger::malloc_empty_log_line() noexcept {
    return master_logger().malloc_empty_log_line();
}

// -----------------------------------------------------------------------------
// Returns log line.
// -----------------------------------------------------------------------------
void atb::logger::free_log_line(char* line) noexcept {
    master_logger().free_log_line(line);
}