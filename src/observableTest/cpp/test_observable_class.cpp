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
        const std::string name;
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

TEST_F(Observable_class_test, throw_exception_when_attach_null_int_observer_with_rvalue_key) {
    ASSERT_THROW(intobsrv.attach(std::string{"null observer"}, std::unique_ptr<test_observer<int>>()), std::invalid_argument);
}

TEST_F(Observable_class_test, throw_exception_when_attach_null_string_observer_with_rvalue_key) {
    ASSERT_THROW(strobsrv.attach("null observer", std::unique_ptr<test_observer<std::string>>()), std::invalid_argument);
}

TEST_F(Observable_class_test, throw_exception_when_attach_null_int_observer_with_lvalue_key) {
    std::string lvalue_key = "call attach(std::string&, ...)";
    ASSERT_THROW(intobsrv.attach(lvalue_key, observable<int>::observer_ptr{}), std::invalid_argument);
}

TEST_F(Observable_class_test, throw_exception_when_attach_null_string_observer_with_lvalue_key) {
    std::string lvalue_key = "call attach(std::string&, ...)";
    ASSERT_THROW(strobsrv.attach(lvalue_key, observable<std::string>::observer_ptr{}), std::invalid_argument);
}

TEST_F(Observable_class_test, no_throw_when_attach_int_observer_normally_with_rvalue_key) {
    ASSERT_NO_THROW(intobsrv.attach("normal observer", std::make_unique<test_observer<int>>()));
}

TEST_F(Observable_class_test, no_throw_when_attach_string_observer_normally_with_rvalue_key) {
    ASSERT_NO_THROW(strobsrv.attach("normal observer", std::make_unique<test_observer<std::string>>()));
}

TEST_F(Observable_class_test, no_throw_when_attach_int_observer_normally_with_lvalue_key) {
    std::string lvalue_key = "call attach(std::string&, ...)";
    ASSERT_NO_THROW(intobsrv.attach(lvalue_key, std::make_unique<test_observer<int>>()));
}

TEST_F(Observable_class_test, no_throw_when_attach_string_observer_normally_with_lvalue_key) {
    std::string lvalue_key = "call attach(std::string&, ...)";
    ASSERT_NO_THROW(strobsrv.attach(lvalue_key, std::make_unique<test_observer<std::string>>())); 
}
