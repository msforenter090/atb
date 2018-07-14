#include "tag_cashier.h"

// -----------------------------------------------------------------------------
// std
// -----------------------------------------------------------------------------
#include <new>
#include <string.h>
#include <cassert>

atb::core::tag_cashier::tag_cashier() : max_tags(atb::core::max_tag_count), current_position(0) {
    cached_tags = new (std::nothrow) tag[max_tags];
}

atb::core::tag_cashier::~tag_cashier() {
    delete cached_tags;
    cached_tags = nullptr;
}

bool atb::core::tag_cashier::valid() const {
    return cached_tags != nullptr;
}

int atb::core::tag_cashier::cache(const atb::core::tag& element) {
    for (int i = 0; i < current_position; i++)
        if (memcmp(cached_tags[i].value, element.value, ip_address_bytes) == 0)
            return i;

    // -------------------------------------------------------------------------
    // did not find cached value. try to make new cache entry.
    // lookout for the memory out of bounds.
    // -------------------------------------------------------------------------
    if (current_position == max_tags)
        return -1;

    memcpy(cached_tags[current_position].value, element.value, tag_length);
    current_position++;

    return current_position - 1;
}

const atb::core::tag& atb::core::tag_cashier::cache(const int cached) const {
    assert(cached >= 0 && cached < current_position);
    return cached_tags[cached];
}

void atb::core::tag_cashier::uncache(const int cached) {
    for (int i = cached + 1; i < current_position; i++)
        cached_tags[i - 1] = cached_tags[i];

    memset(static_cast<void*>(cached_tags + current_position - 1), 0, sizeof(tag));
    current_position--;
}

void atb::core::tag_cashier::uncache(tag& element) {
    int cached = cache(element);
    uncache(cached);
}

void atb::core::tag_cashier::clear() {
    memset(static_cast<void*>(cached_tags), 0, sizeof(tag) * max_tags);
    current_position = 0;
}
