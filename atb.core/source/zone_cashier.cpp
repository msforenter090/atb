#include "zone_cashier.h"

// -----------------------------------------------------------------------------
// std
// -----------------------------------------------------------------------------
#include <cassert>

int atb::core::zone_cashier::cache(atb::core::zone& element) {
    for (int i = 0; i < cashier.size(); i++) {
        atb::core::zone& entry = cashier.at(i);
        if (entry.host == element.host)
            return i;
    }

    cashier.push_back(element);
    return cashier.size() - 1; // caching is based on index, we return index.
}

const atb::core::zone& atb::core::zone_cashier::cache(const int cached) const {
    assert(cached >= 0 && cached < cashier.size());
    return cashier.at(cached);
}

void atb::core::zone_cashier::clear() {
    cashier.clear();
}
