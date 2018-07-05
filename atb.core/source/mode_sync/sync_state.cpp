#include "sync_state.h"

bool atb::core::sync::init_sync_state(const atb::core::atb_settings& settings,
                                      int max_tag_number,
                                      atb::common::thread_safe_queue* queue,
                                      atb::core::sync::sync_state& state) {
    state.settings = settings;
    state.queue = queue;

    // -------------------------------------------------------------------------
    // allocate memory for tag zone map
    // -------------------------------------------------------------------------
    state.detection_satate.tag_zone_table = new (std::nothrow)
        atb::core::tag_zone_history[max_tag_count * atb::core::zone_count(settings)];
    if (state.detection_satate.tag_zone_table == nullptr)
        return false;
    memset(state.detection_satate.tag_zone_table, 0,
           max_tag_count * atb::core::zone_count(settings) * sizeof(atb::core::tag_zone_history));

    // -------------------------------------------------------------------------
    // allocated memory for timestamp map
    // -------------------------------------------------------------------------
    state.detection_satate.timstamp_map = new (std::nothrow)
        long[max_tag_count * atb::core::zone_count(settings)];
    if (state.detection_satate.timstamp_map == nullptr)
        return false;
    memset(state.detection_satate.timstamp_map, 0,
           max_tag_count * atb::core::zone_count(settings) * sizeof(long));

    return true;
}

bool atb::core::sync::destroy_sync_state(atb::core::sync::sync_state& state) {
    delete state.detection_satate.timstamp_map;
    state.detection_satate.timstamp_map = nullptr;

    delete state.detection_satate.tag_zone_table;
    state.detection_satate.tag_zone_table = nullptr;

    return true;
}
