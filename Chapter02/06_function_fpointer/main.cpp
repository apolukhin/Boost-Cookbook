#include <boost/function.hpp>
typedef boost::function<void(int)> fobject_t;

// Now this function may accept functional objects
void process_integers(const fobject_t& f);


void my_ints_function(int i);

int main() {
    process_integers(&my_ints_function);
}

#include <assert.h>
void my_ints_function(int i) { assert(i == 10); }
void process_integers(const fobject_t& f) {
    f(10);

#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
    boost::function<int(std::string&&)> f = &something;
    f(std::string("Hello")); // Works
#endif
}
