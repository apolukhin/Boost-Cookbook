#ifndef BOOST_BOOK_CHAPTER12_FOO_HPP
#define BOOST_BOOK_CHAPTER12_FOO_HPP

#include <stdexcept>
struct foo {
    int val_;

    operator int() const;
    bool is_not_null() const;
    void throws() const; // throws(std::logic_error)
};

#endif // BOOST_BOOK_CHAPTER12_FOO_HPP
