#include <boost/variant.hpp>
#include <iostream>
#include <vector>
#include <string>

int main() {
    typedef boost::variant<int, const char*, std::string> my_var_t;
    std::vector<my_var_t> some_values;
    some_values.push_back(10);
    some_values.push_back("Hello there!");
    some_values.push_back(std::string("Wow!"));

    std::string& s = boost::get<std::string>(some_values.back());
    s += " That is great!\n";
    std::cout << s;
}



void example_func() {
    // Default constructor will construct an instance of boost::blank
    boost::variant<boost::blank /*empty state*/, int, const char*, std::string> var;

    // 'which()' method returns an index of a type currently held by variant.
    assert(var.which() == 0); // Empty state

    var = "Hello, dear reader";
    assert(var.which() != 0);
}

void example_func1() {
    boost::variant<int, std::string> variable(0);

    // Following method may throw a boost::bad_get
    // exception if actual value in variable is not an int
    int s1 = boost::get<int>(variable);

    // If actual value in variable is not an int will return an NULL pointer.
    int* s2 = boost::get<int>(&variable);


    (void)s1; // Supressing warnings about unused variable
    (void)s2; // Supressing warnings about unused variable
}
