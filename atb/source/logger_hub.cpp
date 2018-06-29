#include "logger_hub.h"

#include <stdlib.h>
#include <iostream>

atb::logger_hub::logger_hub() : console(spdlog::stdout_color_mt("console")) {
}

void atb::logger_hub::debug(const char * const message) noexcept {
    console->debug(message);
}

void atb::logger_hub::info(const char * const message) noexcept {
    console->info(message);
}

void atb::logger_hub::warn(const char * const message) noexcept {
    console->warn(message);
}

void atb::logger_hub::error(const char * const message) noexcept {
    console->error(message);
}

void atb::logger_hub::fatal(const char * const message) noexcept {
    console->critical(message);
}

char* atb::logger_hub::malloc_empty_log_line() noexcept {
    return static_cast<char*>(malloc(1024));
}

void atb::logger_hub::free_log_line(char * line) noexcept {
    free(line);
}
