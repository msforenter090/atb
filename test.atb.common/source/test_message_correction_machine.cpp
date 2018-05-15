#include "test_message_correction_machine.h"

// -----------------------------------------------------------------------------
// custom
// -----------------------------------------------------------------------------
#include "atb.common/message_correction_machine.h"

namespace atb {
    namespace network {

        // ---------------------------------------------------------------------
        // valud input
        // ---------------------------------------------------------------------
        const char valid_input_1[] = { "[7E162E1401]" };
        const char valid_input_2[] = { "[74062FD101]" };
        const char valid_input_3[] = { "[71062FDB01]" };
        const char valid_input_4[] = { "[73062FA501]" };

        // ---------------------------------------------------------------------
        // invalid valud input
        // ---------------------------------------------------------------------
        const char invalid_input_1[] = { "[75062F[6F06" };
        const char invalid_input_2[] = { "2F8501][7006" };
        const char invalid_input_3[] = { "2FDB01][8406" };
        const char invalid_input_4[] = { "2F7F01][7406" };

        const char valid_input_1_comb_2[] = { "[6F062F8501]" };
        const char valid_input_2_comb_3[] = { "[70062FDB01]" };
        const char valid_input_3_comb_4[] = { "[84062F7F01]" };

        void test_message_correction_machine::SetUp() {
        }

        void test_message_correction_machine::TearDown() {
        }

        TEST_F(test_message_correction_machine, test_mcm_instantiation) {
            atb::network::message_correction_machine mcm;

            assert(mcm.data() != nullptr);
            assert(mcm.length() == 0);
        }

        TEST_F(test_message_correction_machine, test_mcm_start_state) {
            atb::network::message_correction_machine mcm;

            mcm.consume(valid_input_1, atb::network::network_message_length);
            EXPECT_EQ(mcm.length(), 0) << __FUNCTION__;
        }

        TEST_F(test_message_correction_machine,
            test_process_multiple_valid_message) {
            atb::network::message_correction_machine mcm;

            mcm.consume(valid_input_1, atb::network::network_message_length);
            mcm.process();

            EXPECT_EQ(mcm.length(), atb::network::network_message_length) 
                << __FUNCTION__;

            EXPECT_EQ(memcmp(mcm.data(), valid_input_1,
                atb::network::network_message_length),
                0) << __FUNCTION__;

            mcm.consume(valid_input_2, atb::network::network_message_length);
            mcm.process();

            EXPECT_EQ(mcm.length(), atb::network::network_message_length)
                << __FUNCTION__;
            EXPECT_EQ(memcmp(mcm.data(), valid_input_2,
                atb::network::network_message_length),
                0) << __FUNCTION__;

            mcm.consume(valid_input_3, atb::network::network_message_length);
            mcm.process();

            EXPECT_EQ(mcm.length(), atb::network::network_message_length)
                << __FUNCTION__;
            EXPECT_EQ(memcmp(mcm.data(), valid_input_3,
                atb::network::network_message_length),
                0) << __FUNCTION__;
        }

        TEST_F(test_message_correction_machine,
            test_process_multiple_mixed_message_start_valid) {
            atb::network::message_correction_machine mcm;

            mcm.consume(valid_input_1, atb::network::network_message_length);
            mcm.process();

            EXPECT_EQ(mcm.length(), atb::network::network_message_length)
                << __FUNCTION__;
            EXPECT_EQ(memcmp(mcm.data(), valid_input_1,
                atb::network::network_message_length),
                0) << __FUNCTION__;

            mcm.consume(invalid_input_1, atb::network::network_message_length);
            mcm.process();

            EXPECT_EQ(mcm.length(), 0) << __FUNCTION__;
            EXPECT_EQ(memcmp(mcm.data(), valid_input_1,
                atb::network::network_message_length),
                0) << __FUNCTION__;

            mcm.consume(invalid_input_2, atb::network::network_message_length);
            mcm.process();

            EXPECT_EQ(mcm.length(), atb::network::network_message_length) << __FUNCTION__;
            EXPECT_EQ(memcmp(mcm.data(), valid_input_1_comb_2,
                atb::network::network_message_length),
                0) << __FUNCTION__;
        }

        TEST_F(test_message_correction_machine, test_process_multiple_invalid) {
            atb::network::message_correction_machine mcm;

            mcm.consume(invalid_input_1, atb::network::network_message_length);
            mcm.process();

            mcm.consume(invalid_input_1, atb::network::network_message_length);
            mcm.process();

            mcm.consume(invalid_input_1, atb::network::network_message_length);
            mcm.process();

            EXPECT_EQ(mcm.length(), 0);
        }
    }
}
