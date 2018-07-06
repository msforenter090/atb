#pragma once

// -----------------------------------------------------------------------------
// boost
// -----------------------------------------------------------------------------
#include <boost/thread.hpp>

// -----------------------------------------------------------------------------
// custom
// -----------------------------------------------------------------------------
#include "atb.core/pipeline.h"
#include "atb.networking/network_junction.h"

namespace atb {
    class application {
    private:
        struct _app_implementation;
        _app_implementation *implementation;

    public:
        application();

        ~application();

        // ---------------------------------------------------------------------
        // initialize and start service
        // ---------------------------------------------------------------------
        bool start();

        // ---------------------------------------------------------------------
        // initialize and start service
        // ---------------------------------------------------------------------
        void stop();
    };
}