#pragma once

// -----------------------------------------------------------------------------
// custom
// -----------------------------------------------------------------------------
#include "atb_settings.h"

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
            void queue_worker();

            // -----------------------------------------------------------------
            /// <summary>
            /// Starts pipeline work (add handler).
            /// </summary>
            // -----------------------------------------------------------------
            bool start();

            // -----------------------------------------------------------------
            /// <summary>
            /// Stops pipeline work (remove handler).
            /// </summary>
            // -----------------------------------------------------------------
            void stop();

            // -----------------------------------------------------------------
            /// <summary>
            /// Free allocated resources during run.
            /// If called beore stop program will probably crash.
            /// </summary>
            // -----------------------------------------------------------------
            bool cleanup();
        };
    }
}