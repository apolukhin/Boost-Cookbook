// developer1.cpp
#include <boost/test/unit_test.hpp>
#include "foo.hpp"

BOOST_AUTO_TEST_CASE(test_no_1) {
    // ...
    foo f1 = {1}, f2 = {2};
    BOOST_CHECK(f1.is_not_null());
    
    BOOST_CHECK_NE(f1, f2);

    BOOST_CHECK_THROW(f1.throws(), std::logic_error);
} // BOOST_AUTO_TEST_CASE(test_no_1)
