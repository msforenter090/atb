#pragma once

namespace atb {
    namespace logger {

        class logger {

        public:
            // -----------------------------------------------------------------
            // Debug callback.
            // -----------------------------------------------------------------
            virtual void debug(const char* const message) noexcept = 0;

            // -----------------------------------------------------------------
            // Info callback.
            // -----------------------------------------------------------------
            virtual void info(const char* const message) noexcept = 0;

            // -----------------------------------------------------------------
            // Warning callback.
            // -----------------------------------------------------------------
            virtual void warn(const char* const message) noexcept = 0;

            // -----------------------------------------------------------------
            // Error callback.
            // -----------------------------------------------------------------
            virtual void error(const char* const message) noexcept = 0;

            // -----------------------------------------------------------------
            // Fatal callback.
            // -----------------------------------------------------------------
            virtual void fatal(const char* const message) noexcept = 0;
        };
    }
}
