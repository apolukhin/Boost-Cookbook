#include <boost/array.hpp>

boost::array<unsigned char, 60> chars_65_125_pre11() {
    boost::array<unsigned char, 60> res;

    const unsigned char offset = 65;
    for (std::size_t i = 0; i < res.size(); ++i) {
        res[i] = i + offset;
    }

    return res;
}


#include <boost/algorithm/cxx11/iota.hpp>
#include <boost/array.hpp>

boost::array<unsigned char, 60> chars_65_125() {
    boost::array<unsigned char, 60> res;
    boost::algorithm::iota(res.begin(), res.end(), 65);
    return res;
}

#include <boost/algorithm/hex.hpp>
#include <iterator>
#include <iostream>

void to_hex_test1() {
    const std::string data = "Hello word";
    boost::algorithm::hex(
        data.begin(), data.end(),
        std::ostream_iterator<char>(std::cout)
    );

    std::cout << '\n';
}

void to_hex_test2() {
    const std::string data = "Hello word";
    boost::algorithm::hex(
        data,
        std::ostream_iterator<char>(std::cout)
    );

    std::cout << '\n';
}

#include <cassert>
int main() {
    assert(chars_65_125_pre11() == chars_65_125());
    to_hex_test1();
    to_hex_test2();
}
