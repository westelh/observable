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

        Observable_class_test(): intobsrv{0}, strobsrv{""} {  }
};
