#pragma once

// -----------------------------------------------------------------------------
// custom
// -----------------------------------------------------------------------------
#include "atb_settings.h"

// -----------------------------------------------------------------------------
// boost
// -----------------------------------------------------------------------------
#include "boost/asio.hpp"
#include "boost/thread.hpp"

namespace atb {
    namespace core {
        class pipeline {

            struct _implementation;

        private:
            struct _implementation *implementation;

            atb::core::atb_settings settings;

            void process_mode();

        public:
            pipeline(atb::core::atb_settings settings);

            ~pipeline();

            // -----------------------------------------------------------------
            /// <summary>
            /// Queue for work.
            /// Adds the thread as a worker.
            /// </summary>
            // -----------------------------------------------------------------
            void queue_worker() noexcept;

            // -----------------------------------------------------------------
            /// <summary>
            /// Starts pipeline work (add handler).
            /// </summary>
            // -----------------------------------------------------------------
            void start();

            // -----------------------------------------------------------------
            /// <summary>
            /// Stops pipeline work (remove handler).
            /// </summary>
            // -----------------------------------------------------------------
            void stop();
        };
    }
}