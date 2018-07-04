#pragma once

// -----------------------------------------------------------------------------
// custom
// -----------------------------------------------------------------------------
#include "global_state.h"

namespace atb {
    namespace core {
        namespace wo {
            // -----------------------------------------------------------------
            // WO state
            // -----------------------------------------------------------------
            typedef struct _wo_state {
                atb_settings settings;
                tag_detection_state detection_state;
            } wo_satate;
        }
    }
}
