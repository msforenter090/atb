#include "zone_cashier.h"

// -----------------------------------------------------------------------------
// custom
// -----------------------------------------------------------------------------
#include "constants.h"

// -----------------------------------------------------------------------------
// std
// -----------------------------------------------------------------------------
#include <cassert>

int atb::core::zone_cashier::cache(zone_ip_address& element) {
    const int ip_length = ip_address_bytes;
    for (int i = 0; i < cashier.size(); i++) {
        zone_ip_address& entry = cashier.at(i);
        if (memcpy(entry.zone_ip_address, element.zone_ip_address, ip_length) == 0)
            return i;
    }

    cashier.push_back(element);
    return cashier.size() - 1; // caching is based on index, we return index.
}

const atb::core::zone_ip_address& atb::core::zone_cashier::cache(const int cached) const {
    assert(cached >= 0 && cached < cashier.size());
    return cashier.at(cached);
}

void atb::core::zone_cashier::clear() {
    cashier.clear();
}
