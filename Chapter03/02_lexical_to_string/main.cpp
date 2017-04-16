#include <assert.h>
#include <boost/lexical_cast.hpp>

void foo1() {
    const std::string s = boost::lexical_cast<std::string>(100);
    assert(s == "100");
}

#include <sstream>
void foo2() {
    // C++ way of converting to strings.
    std::stringstream ss;
    ss << 100;
    std::string s;
    ss >> s;

    // Variable 'ss' will dangle all the way, till the end
    // of scope.
    // Multiple virtual methods were called during
    // conversion.
    assert(s == "100");
}

#include <cstdlib>
void foo3() {
     // C way of converting to strings.
     char buffer[100];
     std::sprintf(buffer, "%i", 100);

     // You will need an unsigned long long int type to
     // count how many times errors were made in 'printf'
     // like functions all around the world. 'printf'
     // functions are a constant security threat!

     // But wait, we still need to construct a std::string.
     const std::string s = buffer;
     // Now we have a 'buffer' variable that is not used.

     assert(s == "100");
}


int main() {
    foo1();
    foo2();
    foo3();
}
