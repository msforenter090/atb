#include "test_zone_cashier.h"

// -----------------------------------------------------------------------------
// custom
// -----------------------------------------------------------------------------
#include "atb.core/zone_cashier.h"

namespace atb {
    namespace core {

        zone_ip_address zone_1;
        zone_ip_address zone_2;
        zone_ip_address zone_3;
        zone_ip_address zone_4;
        zone_ip_address zone_5;
        zone_ip_address zone_6;

        void test_zone_cashier::SetUp() {
            memset(zone_1.zone_ip_address, 0, ip_address_bytes);
            memset(zone_2.zone_ip_address, 0, ip_address_bytes);
            memset(zone_3.zone_ip_address, 0, ip_address_bytes);
            memset(zone_4.zone_ip_address, 0, ip_address_bytes);
            memset(zone_5.zone_ip_address, 0, ip_address_bytes);
            memset(zone_6.zone_ip_address, 0, ip_address_bytes);

            memcpy(zone_1.zone_ip_address, "192.168.1.1\0", strlen("192.168.1.1\0"));
            memcpy(zone_2.zone_ip_address, "192.168.1.2\0", strlen("192.168.1.2\0"));
            memcpy(zone_3.zone_ip_address, "192.168.1.3\0", strlen("192.168.1.3\0"));
            memcpy(zone_4.zone_ip_address, "192.168.1.4\0", strlen("192.168.1.4\0"));
            memcpy(zone_5.zone_ip_address, "192.168.1.5\0", strlen("192.168.1.5\0"));
            memcpy(zone_6.zone_ip_address, "192.168.1.6\0", strlen("192.168.1.6\0"));
        }

        void test_zone_cashier::TearDown() {
        }

        TEST_F(test_zone_cashier, test_zone_cashier_caching_new_cache_entries) {
            zone_cashier zc;

            ASSERT_EQ(0, zc.cache(zone_1));
            ASSERT_EQ(1, zc.cache(zone_2));
            ASSERT_EQ(2, zc.cache(zone_3));
            ASSERT_EQ(3, zc.cache(zone_4));
            ASSERT_EQ(4, zc.cache(zone_5));
            ASSERT_EQ(5, zc.cache(zone_6));
        }

        TEST_F(test_zone_cashier, test_zone_cashier_caching_mixed_cache_entries) {
            zone_cashier zc;

            // New entries.
            ASSERT_EQ(0, zc.cache(zone_1));
            ASSERT_EQ(1, zc.cache(zone_2));
            ASSERT_EQ(2, zc.cache(zone_3));
            ASSERT_EQ(3, zc.cache(zone_4));

            ASSERT_EQ(1, zc.cache(zone_2));
            ASSERT_EQ(3, zc.cache(zone_4));

            zc.clear();
            ASSERT_EQ(0, zc.cache(zone_3));
            ASSERT_EQ(1, zc.cache(zone_1));
            ASSERT_EQ(2, zc.cache(zone_2));
        }

        TEST_F(test_zone_cashier, test_zone_cashier_caching_mixed_uncache_entries) {
            zone_cashier zc;

            // New entries.
            ASSERT_EQ(0, zc.cache(zone_1));
            ASSERT_EQ(1, zc.cache(zone_2));
            ASSERT_EQ(2, zc.cache(zone_3));
            ASSERT_EQ(3, zc.cache(zone_4));
            ASSERT_EQ(4, zc.cache(zone_5));
            ASSERT_EQ(5, zc.cache(zone_6));

            const zone_ip_address& un_5 = zc.cache(4);
            const zone_ip_address& un_6 = zc.cache(5);
            const zone_ip_address& un_1 = zc.cache(0);

            ASSERT_EQ(0, memcmp(un_1.zone_ip_address, zone_1.zone_ip_address, ip_address_bytes));
            ASSERT_EQ(0, memcmp(un_5.zone_ip_address, zone_5.zone_ip_address, ip_address_bytes));
            ASSERT_EQ(0, memcmp(un_6.zone_ip_address, zone_6.zone_ip_address, ip_address_bytes));
        }
    }
}
