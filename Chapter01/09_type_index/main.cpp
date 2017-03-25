#include <iostream>
#include <typeinfo>

template <class T>
void do_something(const T& x) {
    std::cout << "T is " << typeid(T).name() << std::endl;

    (void)x;
}


void test1() {
    auto&& x = 42;
    std::cout << "x is "
              << typeid(decltype(x)).name()
              << std::endl;

    (void)x;
}

#include <iostream>
#include <boost/type_index.hpp>
namespace bti = boost::typeindex;

template <class T>
void do_something_again(const T& x) {
    std::cout << "T is " << boost::typeindex::type_id<T>() << std::endl;

    (void)x;
}


void test2() {
    auto&& x = 42;
    std::cout << "x is "
              << boost::typeindex::type_id_with_cvr<decltype(x)>()
              << std::endl;

    (void)x;
}


int main () {
    do_something(1.0);
    test1();
    do_something_again(1.0);
    test2();
}



