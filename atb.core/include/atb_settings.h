#pragma once

#include <string>

namespace atb {
    namespace core {

        class atb_settings_loader;

        class atb_settings {
            friend class atb_settings_loader;

        public:
            std::string ss;
        };
    }
}