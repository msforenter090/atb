#ifdef _WIN32
#include <vld.h>
#endif

/ -----------------------------------------------------------------------------
// custom
// -----------------------------------------------------------------------------
#include "application.h"

int main(int argc, char** argv) {
    atb::application application;
    application.start();
    boost::this_thread::sleep_for(boost::chrono::milliseconds(6000));
    application.stop();
#ifdef _WIN32
    system("pause");
#endif
    return 0;
}

