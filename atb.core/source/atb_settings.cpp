#include "atb_settings.h"

atb::core::atb_settings::atb_settings() noexcept {
}

unsigned short atb::core::atb_settings::zone_message_count() const noexcept {
    return z_message_count;
}

unsigned long atb::core::atb_settings::zone_timeout() const noexcept {
    return z_timeout;
}

const atb::core::zone& atb::core::atb_settings::staging() const noexcept {
    return z_staging;
}

const atb::core::zone& atb::core::atb_settings::storage() const noexcept {
    return z_storage;
}

const atb::core::zone& atb::core::atb_settings::decommission() const noexcept {
    return z_decommission;
}

int atb::core::atb_settings::zone_number() const noexcept {
    return all_zones.size();
}
