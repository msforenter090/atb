#include "mode_sync.h"

// -----------------------------------------------------------------------------
// std
// -----------------------------------------------------------------------------
#include <stdio.h>

// -----------------------------------------------------------------------------
// logger
// -----------------------------------------------------------------------------
#include "atb.common/logger.h"

using namespace atb::common;
using namespace atb::core;

atb::core::sync::mode_sync::mode_sync() : mode_handler() {
}

bool atb::core::sync::mode_sync::setup(const atb_settings& settings, thread_safe_queue* queue) noexcept {
    // -------------------------------------------------------------------------
    // allocate and init memory
    // -------------------------------------------------------------------------
    return atb::core::sync::init_sync_state(settings, atb::core::max_tag_count,
                                            queue, state);
}

void atb::core::sync::mode_sync::handle() {
    std::queue<network_message> messages;

    {
        boost::lock_guard<boost::mutex> lock_guard(state.queue->lock);
        std::swap(state.queue->messages, messages);
    }

    raii_log_line log_line;
    while (!messages.empty()) {
        network_message msg = messages.front();
        messages.pop();
        format_line(log_line.ptr, "Rcg: %s\0", msg.tag);
        info(log_line.ptr);
    }
}

bool atb::core::sync::mode_sync::cleanup() noexcept {
    // -------------------------------------------------------------------------
    // release and cleanup
    // -------------------------------------------------------------------------
    return atb::core::sync::destroy_sync_state(state);
}