// -----------------------------------------------------------------------------
// Used to make a service or damonize the thread to a service.
// -----------------------------------------------------------------------------

#pragma once

// -----------------------------------------------------------------------------
// Custom.
// -----------------------------------------------------------------------------
#include<platform.h>

namespace atb {
	namespace platform {
        // ---------------------------------------------------------------------
        // Service thread callback.
        // ---------------------------------------------------------------------
        typedef void (*service_thread)();

        class daemonizer {
        public:
            BYTE8 daemonize(service_thread service) const;
        };

    }
}
