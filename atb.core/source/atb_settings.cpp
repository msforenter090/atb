#include "atb_settings.h"

atb::core::atb_settings::atb_settings() noexcept {
}

unsigned short atb::core::atb_settings::zone_message_count() const noexcept {
    return z_message_count;
}

unsigned long atb::core::atb_settings::zone_timeout() const noexcept {
    return z_timeout;
}
