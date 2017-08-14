struct fallback;

template <
        class Func,
        class Param,
        class Cond,
        class Fallback = fallback>
struct apply_if;

#include <boost/mpl/apply.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>

//#define USE_INCORRECT_APPLY_IF
#ifndef USE_INCORRECT_APPLY_IF

template <class Func, class Param, class Cond, class Fallback>
struct apply_if {
    typedef typename boost::mpl::apply<
        Cond, Param
    >::type condition_t;

    typedef boost::mpl::apply<Func, Param> applied_type;

    typedef typename boost::mpl::eval_if_c<
        condition_t::value,
        applied_type,
        boost::mpl::identity<Fallback>
    >::type type;
};

#else // USE_INCORRECT_APPLY_IF

template <class Func, class Param, class Cond, class Fallback>
struct apply_if {
    typedef typename boost::mpl::apply<
        Cond, Param
    >::type condition_t;

    // Incorrect: metafunction is evaluated when `::type` called.
    typedef typename boost::mpl::apply<Func, Param>::type applied_type;

    typedef typename boost::mpl::if_c<
        condition_t::value,
        applied_type,
        boost::mpl::identity<Fallback>
    >::type type;
};

#endif // USE_INCORRECT_APPLY_IF

#include <boost/static_assert.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/make_unsigned.hpp>
#include <boost/type_traits/is_same.hpp>

using boost::mpl::_1;
using boost::mpl::_2;

typedef apply_if<
    boost::make_unsigned<_1>,
    int,
    boost::is_integral<_1>
>::type res1_t;

BOOST_STATIC_ASSERT((
    boost::is_same<res1_t, unsigned int>::value
));


// Will fail with static assertion somewhere deeply in the implementation
// of boost::make_unsigned<_1> if we do not evaluate the function lazily.
typedef apply_if<
    boost::make_unsigned<_1>,
    float,
    boost::is_integral<_1>
>::type res2_t;

BOOST_STATIC_ASSERT((
    boost::is_same<res2_t, fallback>::value
));

/*
// eval_if_c implementation example 

template<bool C, typename F1, typename F2>
struct eval_if_c {
    typedef typename if_c<C,F1,F2>::type f_;
    typedef typename f_::type type; // call `::type` only for one parameter
};

*/

int main() {}
