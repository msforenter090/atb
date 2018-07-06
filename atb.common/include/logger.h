#pragma once

namespace atb {
    namespace common {

        // ---------------------------------------------------------------------
        // max log line in length
        // ---------------------------------------------------------------------
        const int max_log_line_length = 1024;

        // ---------------------------------------------------------------------
        // Debug callback.
        // ---------------------------------------------------------------------
        extern void debug(const char* const message);

        // ---------------------------------------------------------------------
        // Info callback.
        // ---------------------------------------------------------------------
        extern void info(const char* const message);

        // ---------------------------------------------------------------------
        // Warning callback.
        // ---------------------------------------------------------------------
        extern void warn(const char* const message);

        // ---------------------------------------------------------------------
        // Error callback.
        // ---------------------------------------------------------------------
        extern void error(const char* const message);

        // ---------------------------------------------------------------------
        // Fatal callback.
        // ---------------------------------------------------------------------
        extern void fatal(const char* const message);

        // ---------------------------------------------------------------------
        // Reserves log line.
        // ---------------------------------------------------------------------
        extern char* malloc_empty_log_line();

        // ---------------------------------------------------------------------
        // Returns log line.
        // ---------------------------------------------------------------------
        extern void free_log_line(char* line);

        // ---------------------------------------------------------------------
        // Format log line.
        // ---------------------------------------------------------------------
        extern void format_line(char* line, const char* fmt, ...);

        class raii_log_line {
        public:
            char* ptr;
            raii_log_line() : ptr(malloc_empty_log_line()) {
            }

            ~raii_log_line() {
                free_log_line(ptr);
            }
        };
    }
}
