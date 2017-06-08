#include "foo.hpp"

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

