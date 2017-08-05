#include <iostream>
#include <typeinfo>

template <class T>
void do_something(const T& x) {
    std::cout << "T is " << typeid(T).name() << std::endl;

    (void)x;
}


void sample1() {
    auto&& x = 42;
    std::cout << "x is "
              << typeid(decltype(x)).name()
              << std::endl;

    (void)x;
}

#include <iostream>
#include <boost/type_index.hpp>

template <class T>
void do_something_again(const T& x) {
    std::cout << "T is " << boost::typeindex::type_id<T>() << std::endl;

    (void)x;
}



#include <boost/type_index.hpp>

void sample2() {
    auto&& x = 42;
    std::cout << "x is "
              << boost::typeindex::type_id_with_cvr<decltype(x)>()
              << std::endl;

    (void)x;
}


int main () {
    do_something(1.0);
    sample1();
    do_something_again(1.0);
    sample2();
}



