#include "mode_wo.h"

bool atb::core::mode_wo::setup(const atb::core::atb_settings& settings,
                               atb::common::thread_safe_queue* queue) noexcept {
    return true;
}

void atb::core::mode_wo::handle() {
}

bool atb::core::mode_wo::cleanup() noexcept {
    return true;
}