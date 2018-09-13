#ifdef _WIN32
#include <vld.h>
#endif

// -----------------------------------------------------------------------------
// custom
// -----------------------------------------------------------------------------
#include "application.h"
#include "atb.platform/daemonizer.h"

#include<iostream>
void my_service();

int main(int argc, char** argv) {
    atb::platform::daemonizer d;
    d.daemonize(my_service);
    // my_service();
    #ifdef _WIN32
    system("pause");
#endif
    return 0;
}

void my_service() {
    atb::application application;
    application.start();
    boost::this_thread::sleep_for(boost::chrono::milliseconds(6000));
    application.stop();
    std::cout << "Hello Daemon." << std::endl;
}
