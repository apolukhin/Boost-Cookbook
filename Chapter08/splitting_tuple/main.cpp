#include <boost/fusion/include/remove_if.hpp>
#include <boost/type_traits/is_arithmetic.hpp>

template <class Sequence>
typename boost::fusion::result_of::remove_if<
    const Sequence, 
    boost::is_arithmetic<boost::mpl::_1> 
>::type get_nonarithmetics(const Sequence& seq) 
{
    return boost::fusion::remove_if< 
        boost::is_arithmetic<boost::mpl::_1> 
    >(seq);
}

template <class Sequence>
typename boost::fusion::result_of::remove_if<
    const Sequence, 
    boost::mpl::not_< boost::is_arithmetic<boost::mpl::_1> >
>::type get_arithmetics(const Sequence& seq) 
{
    return boost::fusion::remove_if< 
        boost::mpl::not_< boost::is_arithmetic<boost::mpl::_1> >
    >(seq);
}

#include <boost/fusion/include/vector.hpp>
#include <cassert>
#include <boost/fusion/include/at_c.hpp>
#include <boost/blank.hpp>
int main() {

    typedef boost::fusion::vector<
        int, boost::blank, boost::blank, float
    > tup1_t;
    tup1_t tup1(8, boost::blank(), boost::blank(), 0.0);

    boost::fusion::vector<boost::blank, boost::blank> res_na
        = get_nonarithmetics(tup1);
    boost::fusion::vector<int, float> res_a = get_arithmetics(tup1);
    assert(boost::fusion::at_c<0>(res_a) == 8);


    (void)res_na;
}

#include <boost/fusion/include/mpl.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/type_traits/remove_const.hpp>
template <class Sequence>
struct make_nonconst: boost::mpl::transform<
    Sequence,
    boost::remove_const<boost::mpl::_1>
> {};

typedef boost::fusion::vector<
    const int, const boost::blank, boost::blank
> type1;
typedef make_nonconst<type1>::type nc_type;

BOOST_STATIC_ASSERT((boost::is_same<
    boost::fusion::result_of::value_at_c<nc_type, 0>::type,
    int
>::value));

BOOST_STATIC_ASSERT((boost::is_same<
    boost::fusion::result_of::value_at_c<nc_type, 1>::type,
    boost::blank
>::value));

BOOST_STATIC_ASSERT((boost::is_same<
    boost::fusion::result_of::value_at_c<nc_type, 2>::type,
    boost::blank
>::value));
