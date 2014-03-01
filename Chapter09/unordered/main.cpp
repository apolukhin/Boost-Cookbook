#include <boost/unordered_map.hpp>

#include <string>
#include <map>
#include <iostream>
#include <assert.h>
#include <boost/lexical_cast.hpp>

#include <boost/unordered_set.hpp>
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
    
    strings.insert("CZ"); strings.insert("CD");
    strings.insert("A"); strings.insert("B");

    std::copy(
        strings.begin(),
        strings.end(),
        std::ostream_iterator<std::string>(std::cout, "  ")
    );
}


template <class T>
std::size_t test_default() {
    // Constants
    const std::size_t ii_max = 20000000;
    const std::string s("Test string");
    
    T map;
    
    for (std::size_t ii = 0; ii < ii_max; ++ii) {
        map[s + boost::lexical_cast<std::string>(ii)] = ii;
    }

    // Inserting once more
    for (std::size_t ii = 0; ii < ii_max; ++ii) {
        map[s + boost::lexical_cast<std::string>(ii)] = ii;
    }

    return map.size();
}

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


int main(int argc, char* argv[]) {
    if (argc < 2) {
        example();

        std::cout << "boost::unordered_set<std::string> : ";
        output_example<boost::unordered_set<std::string> >();
        std::cout << "\nstd::set<std::string> : ";
        output_example<std::set<std::string> >();
        std::cout << '\n';

        boost::unordered_set<my_type> mt;
        mt.insert(my_type());
        return 0;
    }

    switch (argv[1][0]) {
    case 'h': std::cout << "HASH matched: " << test_default< boost::unordered_map<std::string, std::size_t> >();  break;
    case 's': std::cout << "STD matched: " << test_default<std::map<std::string, std::size_t> >();  break;
    default: assert(false); return -2;
    }

    std::cout << '\n';
}

