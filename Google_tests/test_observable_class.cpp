#include "gtest/gtest.h"
#include "observable.hpp"
using namespace testing;

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

class Observable_class_test: public ::testing::Test {
    public:
        constexpr static int initial_value = 100;

        observable<int> intobsrv;

        Observable_class_test(): intobsrv{initial_value} { }
};

TEST_F(Observable_class_test, constructionTest) {
    ASSERT_EQ(intobsrv.getValue(), initial_value);
}

TEST_F(Observable_class_test, updateTest) {
    int old = initial_value;
    int new_ = 10023;

    intobsrv.add_observer_emplace([&old, &new_](const int& o, const int& n){
        ASSERT_EQ(o, old);
        ASSERT_EQ(n, new_);
    });

    intobsrv.setValue(new_);

    old = new_;
    new_ = 43438;

    intobsrv.setValue(new_);
}


