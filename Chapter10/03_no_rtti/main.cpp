#include <boost/config.hpp>


#if !defined(BOOST_NO_RTTI) \
    && !defined(BOOST_NO_CXX11_HDR_TYPEINDEX)

#include <typeindex>
using std::type_index;

template <class T>
type_index type_id() {
    return typeid(T);
}

#else

#include <cstring>
#include <iosfwd> // std::basic_ostream
#include <boost/current_function.hpp>

struct type_index {
    const char* name_;

    explicit type_index(const char* name)
        : name_(name)
    {}

    const char* name() const { return name_; }
};

inline bool operator == (type_index v1, type_index v2) {
    return !std::strcmp(v1.name_, v2.name_);
}

inline bool operator != (type_index v1, type_index v2) {
    return !(v1 == v2);
}

template <class Char, class Trait>
inline std::basic_ostream<Char, Trait>& operator << (std::basic_ostream<Char, Trait>& os, const type_index& t) {
    return os << t.name_;
}

template <class T>
inline type_index type_id() {
    return type_index(BOOST_CURRENT_FUNCTION);
}

#endif

void test();

#include <iostream>
#include <cassert>

int main() {
    assert(type_id<unsigned int>() == type_id<unsigned>());
    assert(type_id<double>() != type_id<long double>());

    std::cout << type_id<double>().name();

    test();
}

#include <boost/type_index.hpp>

void test() {
    using boost::typeindex::type_id;

    assert(type_id<unsigned int>() == type_id<unsigned>());
    assert(type_id<double>() != type_id<long double>());
}

