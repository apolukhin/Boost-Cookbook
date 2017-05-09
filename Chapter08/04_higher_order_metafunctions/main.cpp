typedef void(*function_t)(int);

function_t higher_order_function1();
void higher_order_function2(function_t f);
function_t higher_order_function3(function_t f);

template <class Param1, class Param2, class Func1, class Func2>
struct coalesce;

#include <boost/mpl/apply.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_same.hpp>

template <class Param1, class Param2, class Func1, class Func2>
struct coalesce {
    typedef typename boost::mpl::apply<Func1, Param1>::type type1;
    typedef typename boost::mpl::apply<Func2, Param2>::type type2;

    typedef typename boost::mpl::if_<
        boost::is_same< boost::mpl::false_, type1>,
        type2,
        type1
    >::type type;
};


#include <boost/static_assert.hpp>
#include <boost/mpl/not.hpp>

using boost::mpl::_1;
using boost::mpl::_2;

typedef coalesce<
    boost::mpl::true_,
    boost::mpl::true_,
    boost::mpl::not_<_1>,
    boost::mpl::not_<_1>
>::type res1_t;
BOOST_STATIC_ASSERT((!res1_t::value));

typedef coalesce<
    boost::mpl::true_,
    boost::mpl::false_,
    boost::mpl::not_<_1>,
    boost::mpl::not_<_1>
>::type res2_t;
BOOST_STATIC_ASSERT((res2_t::value));

typedef coalesce<
    boost::mpl::false_,
    boost::mpl::false_,
    boost::mpl::not_<_1>,
    boost::mpl::not_<boost::mpl::not_<_1> >
>::type res3_t;
BOOST_STATIC_ASSERT((res3_t::value));

typedef coalesce<
    boost::mpl::false_,
    boost::mpl::true_,
    boost::mpl::not_<_1>,
    boost::mpl::not_<boost::mpl::not_<_1> >
>::type res4_t;
BOOST_STATIC_ASSERT((res4_t::value));



#include <iostream>
#include <typeinfo>
int main() {
    // std::cerr << typeid(res2_t).name() << '\n';
}
