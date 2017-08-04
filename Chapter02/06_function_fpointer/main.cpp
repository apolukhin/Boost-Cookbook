#include <boost/function.hpp>
typedef boost::function<void(int)> fobject_t;

// Now this function may accept functional objects
void process_integers(const fobject_t& f);


void my_ints_function(int i);

int main() {
    process_integers(&my_ints_function);
}

#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
#include <string>
int something(std::string&&){ return 0; }
#endif


#include <cassert>
void my_ints_function(int i) { assert(i == 10); }
void process_integers(const fobject_t& fun) {
    fun(10);

#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
    boost::function<int(std::string&&)> f = &something;
    f(std::string("Hello")); // Works
#endif
}
