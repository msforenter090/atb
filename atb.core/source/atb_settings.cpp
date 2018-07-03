#include "atb_settings.h"

atb::core::atb_settings::atb_settings() {
}

unsigned short atb::core::atb_settings::zone_message_count() const {
    return z_message_count;
}

unsigned long atb::core::atb_settings::zone_timeout() const {
    return z_timeout;
}

const atb::core::zone& atb::core::atb_settings::staging() const {
    return z_staging;
}

const atb::core::zone& atb::core::atb_settings::storage() const {
    return z_storage;
}

const atb::core::zone& atb::core::atb_settings::decommission() const {
    return z_decommission;
}

int atb::core::atb_settings::zone_number() const {
    return all_zones.size();
}

atb::core::work_mode atb::core::atb_settings::mode() const {
    return s_mode;
}
