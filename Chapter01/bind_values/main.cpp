#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <algorithm>
#include <functional>
#include <string>
#include <assert.h>

void foo() {

    boost::array<int, 12> values = {{1, 2, 3, 4, 5, 6, 7, 100, 99, 98, 97, 96}};

    // Counting values greater or equal to 5
    std::size_t count0 = std::count_if(values.begin(), values.end(),
    std::bind1st(std::less<int>(), 5));
    std::size_t count1 = std::count_if(values.begin(), values.end(),
    boost::bind(std::less<int>(), 5, _1));
    assert(count0 == count1);

    // Counting values less than 5
    count0 = std::count_if(values.begin(), values.end(),
    std::bind2nd(std::less<int>(), 5));
    count1 = std::count_if(values.begin(), values.end(),
    boost::bind(std::less<int>(), _1, 5));
    assert(count0 == count1);

    boost::array<std::string, 3>  str_values = {{"We ", "are", " the champions!"}};

    // Counting empty strings
    count0 = std::count_if(str_values.begin(), str_values.end(),
    std::mem_fun_ref(&std::string::empty));
    count1 = std::count_if(str_values.begin(), str_values.end(),
    boost::bind(&std::string::empty, _1));
    assert(count0 == count1);

    // Counting strings with length less than 5

    // That code won't compile! And it is hard to understand
    //count0 = std::count_if(str_values.begin(), str_values.end(),
    //std::bind2nd(
    //    std::bind1st(
    //        std::less<std::size_t>(),
    //        std::mem_fun_ref(&std::string::size)
    //    )
    //, 5
    //));

    // This will become much more readable,
    // when you get used to bind
    count1 = std::count_if(str_values.begin(), str_values.end(),
    boost::bind(std::less<std::size_t>(), boost::bind(&std::string::size, _1), 5));
    assert(2 == count1);

    std::string s("Expensive copy constructor of std::string will be called when binding");
    count0 = std::count_if(str_values.begin(), str_values.end(), std::bind2nd(std::less<std::string>(), s));
    count1 = std::count_if(str_values.begin(), str_values.end(), boost::bind(std::less<std::string>(), _1, s));
    assert(count0 == count1);

} // foo

#include <boost/ref.hpp>

void wierd_appender(std::string& to, const std::string& from) {
    to += from;
};

void foo2() {

    std::size_t count0;
    std::size_t count1;
    boost::array<std::string, 3>  str_values = {{"We ", "are", " the champions!"}};


    std::string s("Expensive copy constructor of std::string now won't becalled when binding");
    count0 = std::count_if(str_values.begin(), str_values.end(), std::bind2nd(std::less<std::string>(), boost::cref(s)));
    count1 = std::count_if(str_values.begin(), str_values.end(), boost::bind(std::less<std::string>(), _1, boost::cref(s)));
    assert(count0 == count1);



    std::string result;
    std::for_each(str_values.cbegin(), str_values.cend(), boost::bind(&wierd_appender, boost::ref(result), _1));
    assert(result == "We are the champions!");

} // foo2


int main () {
    foo();
    foo2();

    return 0;
}



