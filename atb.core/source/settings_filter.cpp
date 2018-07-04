#include "settings_filter.h"

int atb::core::zone_count(const atb::core::atb_settings& settings) {
    int custom_zones = settings.zone_number();
    if (settings.mode() == work_mode::WORK_ORDER)
        return custom_zones + 2;    // + 2 for storage and staging
    return custom_zones;
}
