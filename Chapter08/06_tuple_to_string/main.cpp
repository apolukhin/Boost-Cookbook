#include <boost/lexical_cast.hpp>
#include <boost/noncopyable.hpp>

struct stringize_functor: boost::noncopyable {
private:
    std::string& result;

public:
    explicit stringize_functor(std::string& res)
        : result(res)
    {}

    template <class T>
    void operator()(const T& v) const {
        result += boost::lexical_cast<std::string>(v);
    }
};

#include <boost/fusion/include/for_each.hpp>

template <class Sequence>
std::string stringize(const Sequence& seq) {
    std::string result;
    boost::fusion::for_each(seq, stringize_functor(result));
    return result;
}



void tuple_example();
void fusion_tuple_example();
std::string stringize_tup2_example();
void std_tuple_example();


#include <iostream>
#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/adapted/boost_tuple.hpp>
#include <boost/fusion/adapted/std_pair.hpp>
#include <boost/fusion/adapted/boost_array.hpp>

struct cat{};

std::ostream& operator << (std::ostream& os, const cat& ) {
    return os << "Meow! ";
}

int main() {
    boost::fusion::vector<cat, int, std::string> tup1(cat(), 0, "_0");
    boost::tuple<cat, int, std::string> tup2(cat(), 0, "_0");
    std::pair<cat, cat> cats;
    boost::array<cat, 10> many_cats;

    std::cout << stringize(tup1) << '\n' 
        << stringize(tup2) << '\n'
        << stringize(cats) << '\n'
        << stringize(many_cats) << '\n';

    tuple_example();
    fusion_tuple_example();
    stringize_tup2_example();
    std_tuple_example();
}

#include <string>
#include <cassert>

#include <boost/tuple/tuple.hpp>

#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/include/at_c.hpp>

void tuple_example() {
    boost::tuple<int, int, std::string> tup(1, 2, "Meow");
    assert(boost::get<0>(tup) == 1);
    assert(boost::get<2>(tup) == "Meow");
}

void fusion_tuple_example() {
    boost::fusion::vector<int, int, std::string> tup(1, 2, "Meow");
    assert(boost::fusion::at_c<0>(tup) == 1);
    assert(boost::fusion::at_c<2>(tup) == "Meow");
}

#include <boost/fusion/adapted/boost_tuple.hpp>
std::string stringize_tup2_example() {
    boost::tuple<cat, int, std::string> tup2(cat(), 0, "_0");

    std::string result;

    // Instead of
    // boost::fusion::for_each(tup2, stringize_functor(result));
    // there'll be the following:
    stringize_functor functor(result);
    functor(boost::fusion::at_c<0>(tup2));
    functor(boost::fusion::at_c<1>(tup2));
    functor(boost::fusion::at_c<2>(tup2));

    return result;
}

#if __cplusplus >= 201300
#include <utility>
#include <tuple>

template <class Tuple, class Func, std::size_t... I>
void stringize_cpp11_impl(const Tuple& t, const Func& f, std::index_sequence<I...>) {
    // Oops. Requires C++17 fold expressions feature.
    // (f(std::get<I>(t)), ...);

    int tmp[] = { 0, (f(std::get<I>(t)), 0)... };
    (void)tmp; // Suppressing unused variable warnings.
}

template <class Tuple>
std::string stringize_cpp11(const Tuple& t) {
    std::string result;
    stringize_cpp11_impl(
        t,
        stringize_functor(result),
        std::make_index_sequence< std::tuple_size<Tuple>::value >()
    );
    return result;
}


void std_tuple_example() {
    std::tuple<cat, int, std::string> t(cat(), 6, "_6");
    std::string s = stringize_cpp11(t);
    assert(s == "Meow! 6_6");
}
#else // #if __cplusplus >= 201300
void std_tuple_example() {}
#endif // #if __cplusplus >= 201300
