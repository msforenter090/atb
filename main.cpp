#include <iostream>

#include "spdlog/spdlog.h"

int main(int argc, char** argv) {
    // ------------------------------------------------------------------------
    // Test spdlog on console.
    // ------------------------------------------------------------------------
    auto console = spdlog::stdout_color_mt("console");

    console->info("Welcome to spdlog!");
    console->error("Some error message with arg{}..", 1);
    
    system("pause");
    return 0;
}
