// Boost.LexicalCast way of converting to strings:
#include <cassert>
#include <boost/lexical_cast.hpp>

void lexical_cast_example() {
    const std::string s = boost::lexical_cast<std::string>(100);
    assert(s == "100");
}



// C++ way of converting to strings:
#include <cassert>
#include <sstream>

void cpp_convert_example() {
    std::stringstream ss; // Slow/heavy default constructor.
    ss << 100;
    std::string s;
    ss >> s;

    // Variable 'ss' will dangle all the way, till the end
    // of scope. Multiple virtual methods and heavy 
    // operations were called during the conversion.
    assert(s == "100");
}


// C way of converting to strings:
#include <cassert>
#include <cstdlib>

void c_convert_example() {
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
    lexical_cast_example();
    cpp_convert_example();
    c_convert_example();
}
