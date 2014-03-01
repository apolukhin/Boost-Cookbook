#ifndef BOOST_BOOK_CHAPTER10_EXTERN_TEMPLATES
#define BOOST_BOOK_CHAPTER10_EXTERN_TEMPLATES

// Somewhere in header file

#include <boost/config.hpp>

#include <boost/variant.hpp>
#include <boost/blank.hpp>
#include <string>

#ifndef BOOST_NO_CXX11_EXTERN_TEMPLATE

extern template class boost::variant<
    boost::blank,
    int,
    std::string,
    double
>;

#endif

typedef boost::variant<
    boost::blank,
    int,
    std::string,
    double
> variant_type;

#endif // #ifndef BOOST_BOOK_CHAPTER10_EXTERN_TEMPLATES

