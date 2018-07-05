#pragma once

// -----------------------------------------------------------------------------
// std and boost
// -----------------------------------------------------------------------------
#include <boost/thread.hpp>
#include <queue>

// -----------------------------------------------------------------------------
// custom
// -----------------------------------------------------------------------------
#include "network_message.h"

// -----------------------------------------------------------------------------
// Thread safe queue.
// Users of the instance must lock / unlock guard manually or else dedlock occurs.
// -----------------------------------------------------------------------------

namespace atb {
    namespace common {
        struct _thread_safe_queue {
            boost::mutex lock;
            std::queue<atb::common::network_message> messages;
        };

        typedef struct _thread_safe_queue thread_safe_queue;
    }
}
