#include "logger_hub.h"

#include <stdlib.h>
#include <iostream>

atb::logger_hub::logger_hub() : console(spdlog::stdout_color_mt("console")) {
    spdlog::set_level(spdlog::level::debug);

    for (short i = 0; i < max_log_lines; i++)
        free_log_lines.push_back(malloc(log_line_length));
}

atb::logger_hub::~logger_hub() {
    for (short i = 0; i < max_log_lines; i++)
        free(free_log_lines.at(i));

    free_log_lines.clear();
}

void atb::logger_hub::debug(const char* const message) noexcept {
    console->debug(message);
}

void atb::logger_hub::info(const char* const message) noexcept {
    console->info(message);
}

void atb::logger_hub::warn(const char* const message) noexcept {
    console->warn(message);
}

void atb::logger_hub::error(const char* const message) noexcept {
    console->error(message);
}

void atb::logger_hub::fatal(const char* const message) noexcept {
    console->critical(message);
}

char* atb::logger_hub::malloc_empty_log_line() noexcept {
    boost::lock_guard<boost::mutex> guard(lock);
    assert(!free_log_lines.empty());

    void* log_line = free_log_lines.back();
    free_log_lines.pop_back();
    return static_cast<char*>(log_line);
}

void atb::logger_hub::free_log_line(char* line) noexcept {
    boost::lock_guard<boost::mutex> guard(lock);
    assert(line != nullptr);
    free_log_lines.push_back(line);
}
