// char* vector_advance(char* val);

// char ( &vector_advance( char (&val)[4] ) )[4];


#include <boost/array.hpp>
#include <algorithm>

// Functional object to increment value by one
struct add_1 : public std::unary_function<char, void> {
    void operator()(char& c) const {
        ++ c;
    }

    // If you're not in a mood to write functional objects,
    // but don't know what does 'boost::bind(std::plus<char>(), _1, 1)'
    // do, then read recipe 'Bind a value as a function parameter'
};

typedef boost::array<char, 4> array4_t;
array4_t& vector_advance(array4_t& val) {
    // boost::array has begin(), cbegin(), end(), cend(), rbegin(),
    // size(), empty() and other functions that are common for
    // STL containers
    std::for_each(val.begin(), val.end(), add_1());
    return val;
}

int main() {
    // We can initialize boost::array just like an array in C++11:
    // array4_t val = {0, 1, 2, 3};
    // but in C++03 additional pair of curly brackets is required.
    array4_t val = {{0, 1, 2, 3}};

    // boost::array works like a usual array:
    array4_t val_res;               // it can be default constructible and
    val_res = vector_advance(val);  // assignable
    // if value type supports default construction and assignment

    assert(val.size() == 4);
    assert(val[0] == 1);
    /*val[4];*/ // Will trigger an assert because max index is 3

    // We can make this assert work at compile time.
    // Interested? See recipe 'Check sizes at compile tim'e
    assert(sizeof(val) == sizeof(char) * array4_t::static_size);
    return 0;
}
