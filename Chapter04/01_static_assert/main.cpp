#include <cstring>
#include <boost/array.hpp>

// C++17 has std::byte out of the box!
// Unfortunately this is as C++03 example.
typedef unsigned char byte_t;

template <class T, std::size_t BufSizeV>
void serialize_bad(const T& value, boost::array<byte_t, BufSizeV>& buffer) {
    // TODO: check buffer size.
    std::memcpy(&buffer[0], &value, sizeof(value));
}

namespace example2 {

template <class T, std::size_t BufSizeV>
void serialize_bad(const T& value, boost::array<byte_t, BufSizeV>& buffer) {
    // TODO: think of something better.
    assert(BufSizeV >= sizeof(value));
    std::memcpy(&buffer[0], &value, sizeof(value));
}

} // namespace example 2



#include <boost/static_assert.hpp>
#include <boost/type_traits/has_trivial_copy.hpp>

template <class T, std::size_t BufSizeV>
void serialize(const T& value, boost::array<byte_t, BufSizeV>& buffer) {
    BOOST_STATIC_ASSERT(BufSizeV >= sizeof(value));
    BOOST_STATIC_ASSERT(boost::has_trivial_copy<T>::value);

    std::memcpy(&buffer[0], &value, sizeof(value));
}

BOOST_STATIC_ASSERT(3 >= 1);

struct some_struct { enum enum_t { value = 1}; };
BOOST_STATIC_ASSERT(some_struct::value);

template <class T1, class T2>
struct some_templated_struct {
    enum enum_t { value = (sizeof(T1) == sizeof(T2))};
};
BOOST_STATIC_ASSERT((some_templated_struct<int, unsigned int>::value));

template<class T1, class T2>
struct some_template { 
    BOOST_STATIC_ASSERT(sizeof(T1) == sizeof(T2));
};




#include <iostream>
#include <boost/type_traits/is_unsigned.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_const.hpp>

template <class T1, class T2>
void type_traits_examples(T1& /*v1*/, T2& /*v2*/) {
    // Returns true if T1 is an unsigned number
    std::cout << boost::is_unsigned<T1>::value;

    // Returns true if T1 has exactly the same type, as T2
    std::cout << boost::is_same<T1, T2>::value;

    // This line removes const modifier from type of T1.
    // Here is what will happen with T1 type if T1 is:
    // const int => int
    // int => int
    // int const volatile => int volatile
    // const int& => const int&
    typedef typename boost::remove_const<T1>::type t1_nonconst_t;

    t1_nonconst_t value;
    (void)value;
}

template <class T, std::size_t BufSizeV>
void serialize2(const T& value, boost::array<byte_t, BufSizeV>& buf) {
    BOOST_STATIC_ASSERT_MSG(boost::has_trivial_copy<T>::value,
        "This serialize2 function may be used only "
        "with trivially copyable types."
    );

    BOOST_STATIC_ASSERT_MSG(BufSizeV >= sizeof(value),
        "Can not fit value to buffer. "
        "Make the buffer bigger."
    );

    std::memcpy(&buf[0], &value, sizeof(value));
}

int main() {
    const int i = 1;
    type_traits_examples(i, i);

    // Somewhere in code:
    boost::array<unsigned char, 1> buf;
    serialize_bad('1', buf);
    example2::serialize_bad('1', buf);
    serialize('1', buf);
    serialize2('2', buf);
    //serialize2(std::string("Hello word"), buf);

    (void)buf;
}
