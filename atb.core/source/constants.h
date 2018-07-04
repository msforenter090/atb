#pragma once

namespace atb {
    namespace core {
        // ---------------------------------------------------------------------
        // max number of tags allower in runtime                    (variable)
        // ---------------------------------------------------------------------
        const int max_tag_count = 100 * 1000;

        // ---------------------------------------------------------------------
        // max history length per tag / zone pair                   (variable)
        // ---------------------------------------------------------------------
        const short history_length = 8;

        // ---------------------------------------------------------------------
        // single element in history, 0-255                         (variable)
        // ---------------------------------------------------------------------
        typedef unsigned char history_element;
    }
}
