#pragma once

#include <mutex>
#include <queue>
#include "network_message.h"

// -----------------------------------------------------------------------------
// Thread safe queue.
// Users of the instance must lock / unlock guard manually or else dedlock occurs.
// -----------------------------------------------------------------------------

namespace atb {
    namespace queue {
        struct _thread_safe_queue {
            std::mutex lock;
            std::queue<atb::network::message::network_message> messages;
        };

        typedef struct _thread_safe_queue thread_safe_queue;
    }
}
