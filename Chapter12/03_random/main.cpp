#include <boost/config.hpp>
#include <boost/random/random_device.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include <iostream>

int main() {
    static const std::string provider =
#ifdef BOOST_WINDOWS
        "Microsoft Strong Cryptographic Provider"
#else
        "/dev/urandom"
#endif
    ;

    boost::random_device device(provider);
    boost::random::uniform_int_distribution<unsigned short> random(1000);

    for (unsigned int i = 0; i < 100; ++i) {
        std::cerr << random(device) << '\t';
    }
}
