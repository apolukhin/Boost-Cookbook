#include <boost/tuple/tuple.hpp>
#include <string>

#include <boost/tuple/tuple_comparison.hpp>
#include <assert.h>
#include <set>

void foo1() {
    boost::tuple<int, std::string> almost_a_pair(10, "Hello");
    boost::tuple<int, float, double, int> quad(10, 1.0f, 10.0, 1);


    int i = boost::get<0>(almost_a_pair);
    const std::string& str = boost::get<1>(almost_a_pair);
    double d = boost::get<2>(quad);

    (void) i;
    (void) str;
    (void) d;

    // Tuple comparison operators are
    // defined in header "boost/tuple/tuple_comparison.hpp"
    // Don't forget to include it!
    std::set<boost::tuple<int, double, int> > s;
    s.insert(boost::make_tuple(1, 1.0, 2));
    s.insert(boost::make_tuple(2, 10.0, 2));
    s.insert(boost::make_tuple(3, 100.0, 2));
}

void foo2() {
#ifndef BOOST_NO_CXX11_AUTO_DECLARATIONS
    // Requires C++11
    const auto t = boost::make_tuple(0, -1.0, 2);
    assert(2 == boost::get<2>(t));
    // We can make a compile time assert for type
    // of t. Interested? See chapter 'Compile time tricks'
#endif
}

void foo3() {
    boost::tuple<int, float, double, int> quad(10, 1.0f, 10.0, 1);
    int i;
    float f;
    double d;
    int i2;

    // Passing values from 'quad' variables
    // to variables 'i', 'f', 'd', 'i2'
    boost::tie(i, f, d, i2) = quad;

    assert(i == 10);
    assert(i2 == 1);
}

struct id_name_pair {
    int id;
    std::string name;
};

int main () {
    foo1();
    foo2();
    foo3();
}
