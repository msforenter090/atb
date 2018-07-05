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

bool atb::core::sync::mode_sync::setup(const atb::core::atb_settings& settings,
                                       atb::common::thread_safe_queue* queue) noexcept {
    // -------------------------------------------------------------------------
    // allocate and init memory
    // -------------------------------------------------------------------------
    return atb::core::sync::init_sync_state(settings, atb::core::max_tag_count,
                                            queue, state);
}

void atb::core::sync::mode_sync::handle() {
    std::queue<atb::common::network_message> messages;

    {
        boost::lock_guard<boost::mutex> lock_guard(state.queue->lock);
        std::swap(state.queue->messages, messages);
    }

    atb::common::raii_log_line log_line;
    while (!messages.empty()) {
        atb::common::network_message msg = messages.front();
        messages.pop();
        atb::common::format_line(log_line.ptr, atb::common::max_log_line_length,
                                 "Rcg: %s", msg.tag);
        atb::common::info(log_line.ptr);
    }
}

bool atb::core::sync::mode_sync::cleanup() noexcept {
    // -------------------------------------------------------------------------
    // release and cleanup
    // -------------------------------------------------------------------------
    return atb::core::sync::destroy_sync_state(state);
}