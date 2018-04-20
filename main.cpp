#include <iostream>

#include <vld.h>

// -----------------------------------------------------------------------------
// Logging.
// -----------------------------------------------------------------------------
#include "spdlog/spdlog.h"

#include <iostream>

// -----------------------------------------------------------------------------
// Test network connection.
// -----------------------------------------------------------------------------
#include "network_junction.h"

int main(int argc, char** argv) {
    // ------------------------------------------------------------------------
    // Test spdlog on console.
    // ------------------------------------------------------------------------
    auto console = spdlog::stdout_color_mt("console");

    console->info("Welcome to spdlog!");
    console->error("Some error message with arg{}..", 1);
    atb::network::junction::network_junction nj;
    nj.start();
    //nj.stop();
    return 0;
}
