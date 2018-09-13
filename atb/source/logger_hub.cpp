#include "logger_hub.h"

// -----------------------------------------------------------------------------
// std
// -----------------------------------------------------------------------------
#include <stdlib.h>
#include <iostream>
#include <stdarg.h>

#ifdef __linux__
#define LOG_FILE "/var/log/atb/atb_log.log"
#else
#define LOG_FILE "atb_log.log"
#endif

atb::logger_hub::logger_hub() : console() {
    spdlog::set_level(spdlog::level::debug);

    try {
        console = spdlog::basic_logger_mt("basic_logger", LOG_FILE);
    } catch (const spdlog::spdlog_ex &ex) {
        std::cout << "Log init failed: " << ex.what() << std::endl;
    }
    for (short i = 0; i < max_log_lines; i++)
        free_log_lines.push_back(malloc(log_line_length));
}

atb::logger_hub::~logger_hub() {
    for (short i = 0; i < max_log_lines; i++)
        free(free_log_lines.at(i));

    free_log_lines.clear();
}

void atb::logger_hub::debug(const char* const message) {
    console->debug(message);
}

void atb::logger_hub::info(const char* const message) {
    console->info(message);
}

void atb::logger_hub::warn(const char* const message) {
    console->warn(message);
}

void atb::logger_hub::error(const char* const message) {
    console->error(message);
}

void atb::logger_hub::fatal(const char* const message) {
    console->critical(message);
}

char* atb::logger_hub::malloc_empty_log_line() {
    boost::lock_guard<boost::mutex> guard(lock);
    assert(!free_log_lines.empty());

    void* log_line = free_log_lines.back();
    free_log_lines.pop_back();
    return static_cast<char*>(log_line);
}

void atb::logger_hub::free_log_line(char* line) {
    boost::lock_guard<boost::mutex> guard(lock);
    assert(line != nullptr);
    free_log_lines.push_back(line);
}

