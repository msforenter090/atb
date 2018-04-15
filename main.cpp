#include <iostream>

// ----------------------------------------------------------------------------
// Logging.
// ----------------------------------------------------------------------------
#include "spdlog/spdlog.h"

// ----------------------------------------------------------------------------
// Thread example.
// ----------------------------------------------------------------------------
#include <boost/thread.hpp>
#include <boost/chrono.hpp>
#include <iostream>

void wait(int seconds) {
    boost::this_thread::sleep_for(boost::chrono::seconds{ seconds });
}

void thread() {
    for (int i = 0; i < 5; ++i) {
        wait(1);
        std::cout << i << '\n';
    }
}

int main(int argc, char** argv) {
    // ------------------------------------------------------------------------
    // Test spdlog on console.
    // ------------------------------------------------------------------------
    auto console = spdlog::stdout_color_mt("console");

    console->info("Welcome to spdlog!");
    console->error("Some error message with arg{}..", 1);

    // ------------------------------------------------------------------------
    // Test boost thread.
    // ------------------------------------------------------------------------
    boost::thread t{ thread };
    t.join();

    system("pause");
    return 0;
}
