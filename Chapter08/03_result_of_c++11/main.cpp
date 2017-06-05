template <class T1, class T2>
auto my_function_cpp11(const T1& v1, const T2& v2)
    -> decltype(v1 + v2)
{
    return v1 + v2;
}

#include <cassert>

struct s1 {};
struct s2 {};
struct s3 {};

inline s3 operator + (const s1& /*v1*/, const s2& /*v2*/) {
    return s3();
}

inline s3 operator + (const s2& /*v1*/, const s1& /*v2*/) {
    return s3();
}

#include <boost/type_traits/common_type.hpp>
namespace result_of {

    template <class T1, class T2>
    struct my_function_cpp03 {
        typedef typename boost::common_type<T1, T2>::type type;
    };

    template <> 
    struct my_function_cpp03<s1, s2> {
        typedef s3 type;
    };
    
    template <>
    struct my_function_cpp03<s2, s1> {
        typedef s3 type;
    };
} // namespace result_of

template <class T1, class T2>
typename result_of::my_function_cpp03<T1, T2>::type
    my_function_cpp03(const T1& v1, const T2& v2)
{
    return v1 + v2;
}

int main() {
    s1 v1;
    s2 v2;

    s3 res0 = my_function_cpp11(v1, v2);
    assert(my_function_cpp11('\0', 1) == 1);

    s3 res1 = my_function_cpp03(v1, v2);
    assert(my_function_cpp03('\0', 1) == 1);

    (void)res0;
    (void)res1;
}
