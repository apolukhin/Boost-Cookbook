#include <stdexcept>
struct foo {
    int val_;

    operator int() const;
    bool is_not_null() const;
    void throws() const; // throws(std::logic_error)
};



#define BOOST_TEST_MODULE test_module_name
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(test_no_1) {
    foo f1 = {1}, f2 = {2};
    BOOST_CHECK(f1.is_not_null());

    BOOST_CHECK_NE(f1, f2);

    BOOST_CHECK_THROW(f1.throws(), std::logic_error);
} // BOOST_AUTO_TEST_CASE(test_no_1)

BOOST_AUTO_TEST_CASE(test_no_2) {
    foo f1 = {1}, f2 = {2};
    BOOST_REQUIRE_NE(f1, f2);
    // ...
} // BOOST_AUTO_TEST_CASE(test_no_2)

#define DO_NOT_FAIL
#ifdef DO_NOT_FAIL
foo::operator int() const {
    return val_;
}

bool foo::is_not_null() const {
    return !!val_;
}

void foo::throws() const {
    throw std::logic_error("Expected exception");
}

#else

foo::operator int() const {
    return 0;
}

bool foo::is_not_null() const {
    return !val_;
}

void foo::throws() const {}

#endif // DO_NOT_FAIL
