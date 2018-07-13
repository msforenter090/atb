#pragma once

#include "gtest/gtest.h"

namespace atb {
    namespace core {
        class test_zone_cashier : public ::testing::Test {
        protected:
            void SetUp() override;
            void TearDown() override;
        };
    }
}