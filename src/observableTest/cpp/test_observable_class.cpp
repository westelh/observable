#include "gtest/gtest.h"
#include <string>
#include "observable.hpp"
using namespace testing;

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

template <class T>
class test_observer: public observer<T> {
    public:
        void update(const T&, const T&) override {
        }
};

class Observable_class_test: public ::testing::Test {
    public:
        observable<int> intobsrv;
        observable<std::string> strobsrv;

        Observable_class_test(): intobsrv{0}, strobsrv{""} {  }
};

TEST_F(Observable_class_test, constructionTest) {
    const int c_ori = 50;
    int ori = 70;
    // observable(const T&)
    observable<int> cT{c_ori};
    // observable(T&)
    observable<int> c{ori};
    // observable(T&&)
    observable<int>(80);
}

TEST_F(Observable_class_test, attach_null_observer) {
    ASSERT_THROW(intobsrv.attach(std::unique_ptr<test_observer<int>>()), std::invalid_argument);
    ASSERT_THROW(strobsrv.attach(std::unique_ptr<test_observer<std::string>>()), std::invalid_argument);
}

TEST_F(Observable_class_test, attach_observer_normally) {
    ASSERT_NO_THROW(intobsrv.attach(std::make_unique<test_observer<int>>()));
    ASSERT_NO_THROW(strobsrv.attach(std::make_unique<test_observer<std::string>>()));
}
