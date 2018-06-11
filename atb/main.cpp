#ifdef _WIN32
    #include <vld.h>
#endif

// -----------------------------------------------------------------------------
// Logging.
// -----------------------------------------------------------------------------
#include "spdlog/spdlog.h"

// -----------------------------------------------------------------------------
// boost
// -----------------------------------------------------------------------------
#include <boost/thread.hpp>

// -----------------------------------------------------------------------------
// custom
// -----------------------------------------------------------------------------
#include "atb.networking/network_junction.h"
#include "atb.common/logger.h"

class logger_impl : public atb::logger::logger {

private:
    std::shared_ptr<spdlog::logger> console = spdlog::stdout_color_mt("console");

public:

    logger_impl() {
    }

    void debug(const char* const message) noexcept override {
        console->debug(message);
    }

    void info(const char* const message) noexcept override {
        console->info(message);
    }

    void warn(const char* const message) noexcept override {
        console->warn(message);
    }

    void error(const char* const message) noexcept override {
        console->error(message);
    }

    void fatal(const char* const message) noexcept override {
        console->critical(message);
    }
};

class message_rcv : public atb::network::junction::read_callback {
public:
    void handle(atb::network::address::ip_address_v4 address,
        void const* const data, const unsigned int length) {
        char inter_buff[13];
        memset(inter_buff, 0, 13);
        memcpy(inter_buff, data, length);
        std::cout << inter_buff << std::endl;
    }
};

int main(int argc, char** argv) {
    // -------------------------------------------------------------------------
    // Test spdlog on console.
    // -------------------------------------------------------------------------

    char ip[] = "192.168.1.6";
    logger_impl log_impl;
    message_rcv mrcv;

    atb::network::address::ip_address_v4 add;
    memcpy(add.ip_address, ip, atb::network::address::ip_address_presentation_length);
    add.port = 10001;

    atb::network::junction::network_junction nj(&log_impl, &mrcv);
    nj.remote_devices(&add, 1);

    boost::thread_group th;
    th.create_thread(boost::bind(
        &atb::network::junction::network_junction::queue_for_work,
        &nj)
    );

    th.create_thread(boost::bind(
        &atb::network::junction::network_junction::queue_for_work,
        &nj)
    );

    nj.connect();

    std::cout << "Main: " << boost::this_thread::get_id() << std::endl;
    boost::this_thread::sleep_for(boost::chrono::milliseconds(90000));
    nj.disconnect();

    th.join_all();

    nj.clean();

#ifdef _WIN32
    system("pause");
#endif

    return 0;
}
