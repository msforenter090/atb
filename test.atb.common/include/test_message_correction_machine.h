#pragma once

#include "gtest/gtest.h"

namespace atb {
    namespace network {
        namespace junction {
            class test_message_correction_machine : public ::testing::Test {
            protected:
                void SetUp() override;
                void TearDown() override;
            };
        }
    }
}