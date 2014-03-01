#ifndef MY_LIBRARY_HPP
#define MY_LIBRARY_HPP

#include <boost/config.hpp>

#if defined(MY_LIBRARY_LINK_DYNAMIC)
# if defined(MY_LIBRARY_COMPILATION)
#   define MY_LIBRARY_API BOOST_SYMBOL_EXPORT
# else
#   define MY_LIBRARY_API BOOST_SYMBOL_IMPORT
# endif
#else
# define MY_LIBRARY_API
#endif

int MY_LIBRARY_API foo();
class MY_LIBRARY_API bar { 
public:
    /* ... */ 
    int meow() const;
};

#include <stdexcept>
struct BOOST_SYMBOL_VISIBLE bar_exception
    : public std::exception 
{};

#endif // MY_LIBRARY_HPP
