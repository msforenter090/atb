#include "test_tag_cashier.h"

// -----------------------------------------------------------------------------
// custom
// -----------------------------------------------------------------------------
#include "atb.core/tag_cashier.h"

namespace atb {
    namespace core {

        tag tag_1;
        tag tag_2;
        tag tag_3;
        tag tag_4;

        void test_tag_cashier::SetUp() {
            memcpy(tag_1.value, "000111", tag_length);
            memcpy(tag_2.value, "000112", tag_length);
            memcpy(tag_3.value, "000113", tag_length);
            memcpy(tag_4.value, "000114", tag_length);
        }

        void test_tag_cashier::TearDown() {
        }

        TEST_F(test_tag_cashier, test_tag_cashier) {
            tag_cashier cashier;

            ASSERT_TRUE(cashier.valid());

            ASSERT_EQ(0, cashier.cache(tag_1));
            ASSERT_EQ(1, cashier.cache(tag_2));
            ASSERT_EQ(2, cashier.cache(tag_3));
            ASSERT_EQ(3, cashier.cache(tag_4));

            // Check cached tags.
            {
                const tag& cashed_tag_4 = cashier.cache(3);
                const tag& cashed_tag_3 = cashier.cache(2);
                const tag& cashed_tag_2 = cashier.cache(1);
                const tag& cashed_tag_1 = cashier.cache(0);

                ASSERT_EQ(0, memcmp(cashed_tag_1.value, tag_1.value, tag_length));
                ASSERT_EQ(0, memcmp(cashed_tag_2.value, tag_2.value, tag_length));
                ASSERT_EQ(0, memcmp(cashed_tag_3.value, tag_3.value, tag_length));
                ASSERT_EQ(0, memcmp(cashed_tag_4.value, tag_4.value, tag_length));
            }

            // Remove tag.
            cashier.uncache(0);
            {
                const tag& cashed_tag_3 = cashier.cache(2);
                const tag& cashed_tag_2 = cashier.cache(1);
                const tag& cashed_tag_1 = cashier.cache(0);

                ASSERT_EQ(0, memcmp(cashed_tag_1.value, tag_2.value, tag_length));
                ASSERT_EQ(0, memcmp(cashed_tag_2.value, tag_3.value, tag_length));
                ASSERT_EQ(0, memcmp(cashed_tag_3.value, tag_4.value, tag_length));
            }
        }
    }
}
