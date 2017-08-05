#include <iostream>
#include <stdexcept>

// Negative number that does not store minus sign.
class negative_number {
    unsigned short number_;

public:
    explicit negative_number(unsigned short number = 0)
        : number_(number)
    {}

    // ...
    unsigned short value_without_sign() const {
        return number_;
    }
};

inline std::ostream&
    operator<<(std::ostream& os, const negative_number& num)
{
    os << '-' << num.value_without_sign();
    return os;
}

inline std::istream& operator>>(std::istream& is, negative_number& num)
{
    char ch;
    is >> ch;
    if (ch != '-') {
        throw std::logic_error(
            "negative_number class stores ONLY negative values"
        );
    }

    unsigned short s;
    is >> s;
    num = negative_number(s);
    return is;
}


#include <boost/lexical_cast.hpp>
#include <boost/array.hpp>
#include <cassert>

void example1() {
    const negative_number n
        = boost::lexical_cast<negative_number>("-100");
    assert(n.value_without_sign() == 100);

    const int i = boost::lexical_cast<int>(n);
    assert(i == -100);

    typedef boost::array<char, 10> arr_t;
    const arr_t arr = boost::lexical_cast<arr_t>(n);
    assert(arr[0] == '-');
    assert(arr[1] == '1');
    assert(arr[2] == '0');
    assert(arr[3] == '0');
    assert(arr[4] == 0);
}


template <class CharT>
std::basic_ostream<CharT>&
    operator<<(std::basic_ostream<CharT>& os, const negative_number& num)
{
    os << static_cast<CharT>('-') << num.value_without_sign();
    return os;
}

template <class CharT>
std::basic_istream<CharT>&
    operator>>(std::basic_istream<CharT>& is, negative_number& num)
{
    CharT ch;
    is >> ch;
    if (ch != static_cast<CharT>('-')) {
        throw std::logic_error(
            "negative_number class stores ONLY negative values"
        );
    }
    unsigned short s;
    is >> s;
    num = negative_number(s);
    return is;
}

void example2() {
    const negative_number n = boost::lexical_cast<negative_number>(L"-1");
    assert(n.value_without_sign() == 1);

    typedef boost::array<wchar_t, 10> warr_t;
    const warr_t arr = boost::lexical_cast<warr_t>(n);
    assert(arr[0] == L'-');
    assert(arr[1] == L'1');
    assert(arr[2] == 0);
}


int main() {
    example1();
    example2();
}
