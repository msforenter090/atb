#pragma once

// -----------------------------------------------------------------------------
// custom
// -----------------------------------------------------------------------------
#include "constants.h"

namespace atb {
    namespace core {
        typedef struct _tag {
            char value[tag_length];
        } tag;

        class tag_cashier {
        private:
            // -----------------------------------------------------------------
            // points to next free to allocation position in map.
            // range[0, max_tag_count)
            // -----------------------------------------------------------------
            int max_tags;
            int current_position;

            // -----------------------------------------------------------------
            // holds cache
            // -----------------------------------------------------------------
            tag* cached_tags;

        public:
            tag_cashier();
            ~tag_cashier();

            bool valid() const;

            // -----------------------------------------------------------------
            /// <summary>
            /// Makes new entry in the cache if the entry does not exists and
            /// returns it.
            /// Returns cache if the entry exists.
            /// </summary>
            // -----------------------------------------------------------------
            int cache(const tag& element);

            // -----------------------------------------------------------------
            /// <summary>
            /// Returns cached entry for the given value.
            /// If the cache does not exists calls abort.
            /// </summary>
            // -----------------------------------------------------------------
            const tag& cache(const int cached) const;

            // -----------------------------------------------------------------
            /// <summary>
            /// Removes cached entry.
            /// </summary>
            // -----------------------------------------------------------------
            void uncache(const int cached);

            // -----------------------------------------------------------------
            /// <summary>
            /// Removes cached entry.
            /// </summary>
            // -----------------------------------------------------------------
            void uncache(tag& element);

            // -----------------------------------------------------------------
            /// <summary>
            /// Clear the cache.
            /// </summary>
            // -----------------------------------------------------------------
            void clear();
        };
    }
}