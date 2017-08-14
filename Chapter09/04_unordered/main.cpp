#include <boost/unordered_map.hpp>

#include <map>
#include <iostream>
#include <boost/lexical_cast.hpp>

#include <boost/unordered_set.hpp>
#include <string>
#include <cassert>

void example() {
    boost::unordered_set<std::string> strings;

    strings.insert("This");
    strings.insert("is");
    strings.insert("an");
    strings.insert("example");

    assert(strings.find("is") != strings.cend());
}

#include <set>
template <class T>
void output_example() {
    T strings;
    
    strings.insert("CZ");
    strings.insert("CD");
    strings.insert("A");
    strings.insert("B");

    std::copy(
        strings.begin(),
        strings.end(),
        std::ostream_iterator<std::string>(std::cout, "  ")
    );
}

// Boost.Timer has linkage issues on MSVC.
#ifndef BOOST_MSVC

#include <boost/timer/timer.hpp>

#ifndef BOOST_NO_CXX11_HDR_UNORDERED_MAP
#   include <unordered_map>
#endif
#include <boost/container/map.hpp>

template <class T>
double test_default(const std::size_t ii_max) {
    boost::timer::cpu_timer timer;

    const std::string s("Test string");

    T map;

    for (std::size_t ii = 0; ii < ii_max; ++ii) {
        map[s + boost::lexical_cast<std::string>(ii)] = ii;
    }

    // Asserting.
    for (std::size_t ii = 0; ii < ii_max; ++ii) {
        assert(map[s + boost::lexical_cast<std::string>(ii)] == ii);
    }

    return timer.elapsed().wall;
}


void measure_performance() {
    for (unsigned i = 10; i < 1000000; i *= 10) {
        std::cout << "For " << i << " elements:\n";

        const double boost_map = test_default< boost::container::map<std::string, std::size_t> >(i);
        const double boost_unordered = test_default< boost::unordered_map<std::string, std::size_t> >(i);
        std::cout << "Boost: map is " << boost_map / boost_unordered << " slower than unordered map\n";

#ifndef BOOST_NO_CXX11_HDR_UNORDERED_MAP
        const double std_map = test_default<std::map<std::string, std::size_t> >(i);
        const double std_unordered = test_default<std::unordered_map<std::string, std::size_t> >(i);
        std::cout << "Std: map is " << std_map / std_unordered << " slower than unordered map\n\n";
#endif
    }
}

#else // #ifndef BOOST_MSVC

void measure_performance() {}

#endif

struct my_type {
    int         val1_;
    std::string val2_;
};

inline bool operator == (const my_type& v1, const my_type& v2) {
    return v1.val1_ == v2.val1_ && v1.val2_ == v2.val2_;
}

std::size_t hash_value(const my_type& v) {
    std::size_t ret = 0u;
    
    boost::hash_combine(ret, v.val1_);
    boost::hash_combine(ret, v.val2_);

    return ret;
}


int main() {
    example();

    std::cout << "boost::unordered_set<std::string> : ";
    output_example<boost::unordered_set<std::string> >();
    std::cout << "\nstd::set<std::string> : ";
    output_example<std::set<std::string> >();
    std::cout << '\n';
    
    boost::unordered_set<my_type> mt;
    mt.insert(my_type());

    measure_performance();
}

