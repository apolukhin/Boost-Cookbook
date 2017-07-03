#include <string>
#include <boost/config.hpp>

#define API extern "C" BOOST_SYMBOL_EXPORT

API std::string greeter(const std::string& name) {
    return "They are fast. Faster than you can believe. "
           "Don't turn your back, don't look away, "
           "and don't blink. Good luck, " + name + ".";
}

