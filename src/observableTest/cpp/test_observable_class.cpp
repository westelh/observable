#include "gtest/gtest.h"
#include <string>
#include "observable.hpp"
using namespace testing;

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

class Observable_class_test: public ::testing::Test {
    public:
        observable<int> intobsrv;
        observable<std::string> strobsrv;
};

TEST_F(Observable_class_test, hoge) {
    ASSERT_EQ(intobsrv.get(), 0);
    ASSERT_EQ(strobsrv.get(), "");
}
