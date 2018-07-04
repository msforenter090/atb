#pragma once

// -----------------------------------------------------------------------------
// std
// -----------------------------------------------------------------------------
#include <vector>

// -----------------------------------------------------------------------------
// custom
// -----------------------------------------------------------------------------
#include "constants.h"
#include "settings_filter.h"

namespace atb {
    namespace core {

        // ---------------------------------------------------------------------
        /// <summary>
        /// File contains type definitions and state definitions for all modes.
        /// </summary>
        // ---------------------------------------------------------------------

        // ---------------------------------------------------------------------
        // single tag zone history cell
        // ---------------------------------------------------------------------
        typedef struct _tag_zone_history {
            history_element history[atb::core::history_length];
        } tag_zone_history;

        // ---------------------------------------------------------------------
        // common state
        // ---------------------------------------------------------------------
        typedef struct _tag_detection_state {

            // -----------------------------------------------------------------
            // tag zone table memory
            // -----------------------------------------------------------------
            tag_zone_history* tag_zone_table;
            std::vector<tag_zone_history*> in_use_table_lines;
            std::vector<tag_zone_history*> free_table_lines;

            // -----------------------------------------------------------------
            // timestamp map
            // -----------------------------------------------------------------
            long* timstamp_map;

            // -----------------------------------------------------------------
            // current state, each tag can only be deemed in one zone.
            // -----------------------------------------------------------------
            // some current state variable.
        } tag_detection_state;
    }
}