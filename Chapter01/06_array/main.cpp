#include <boost/array.hpp>
#include <algorithm>

typedef boost::array<char, 4> array4_t;

array4_t& vector_advance(array4_t& val) {
    // C++11 lambda function
    const auto inc = [](char& c){ ++c; };

    // boost::array has begin(), cbegin(), end(), cend(),
    // rbegin(), size(), empty() and other functions that are
    // common for STL containers.
    std::for_each(val.begin(), val.end(), inc);
    return val;
}

int main() {
    // We can initialize boost::array just like an array in C++11:
    // array4_t val = {0, 1, 2, 3};
    // but in C++03 additional pair of curly brackets is required.
    array4_t val = {{0, 1, 2, 3}};

    array4_t val_res;               // it is default constructible
    val_res = vector_advance(val);  // it is assignable

    assert(val.size() == 4);
    assert(val[0] == 1);
    /*val[4];*/ // Will trigger an assert because max index is 3

    // We can make this assert work at compile-time.
    // Interested? See recipe 'Check sizes at compile-time'
    assert(sizeof(val) == sizeof(char) * array4_t::static_size);
}
