#include <cstddef>
int to_int(const char* str, std::size_t length);

#include <boost/version.hpp>
#include <boost/lexical_cast.hpp>

#if (BOOST_VERSION >= 105200)

int to_int(const char* str, std::size_t length) {
    return boost::lexical_cast<int>(str, length);
}

#else

int to_int(const char* str, std::size_t length) {
    return boost::lexical_cast<int>(
        std::string(str, length)
    );
}

#endif

#include <cassert>
int main() {
    assert(to_int("10000000", 3) == 100);
}
