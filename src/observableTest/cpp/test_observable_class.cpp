#include "gtest/gtest.h"
#include "observable.hpp"
using namespace testing;

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(Observable_class_test, hoge) {
	observable<int> wei;
}