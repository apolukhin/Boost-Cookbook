#include <sstream>

void foo1() {
    std::istringstream iss("100");
    int i;
    iss >> i;
    // And now, 'iss' variable will get in the way all the time, till end of the scope
    // It is better not to think, how many unnecessary operations, virtual function calls and memory allocations occurred during those operations
}

#include <cstdlib>
void foo2() {
    char * end;
    int i = std::strtol ("100", &end, 10);
    // Did it converted all the value to int, or stopped somewere in the middle?
    // And now we have 'end' variable will geting in the way
    // By the way, we wante an integer, but strtol returns long int... Did the converted value fit in int?

    (void)i; // Supressing warning about unused variable
}

#include <boost/lexical_cast.hpp>

void foo3() {
    {
    int i = boost::lexical_cast<int>("100");
    (void)i; // Supressing warning about unused variable
    }

    char chars[] = {'1', '0', '0' };
    int i = boost::lexical_cast<int>(chars, 3);
    assert(i == 100);



    try {
        // on x86 short usually may not store values greater than 32767
        short s = boost::lexical_cast<short>("1000000");
        assert(false); // Must not reach this
        (void)s; // Supressing warning about unused variable
    } catch (const boost::bad_lexical_cast& /*e*/) {}


    try {
        int i = boost::lexical_cast<int>("This is not a number!");
        assert(false); // Must not reach this
        (void)i; // Supressing warning about unused variable
    } catch (const boost::bad_lexical_cast& /*e*/) {}
}

#include <locale>
void foo4() {
    std::locale::global(std::locale("ru_RU.UTF8"));
    // In Russia coma sign is used as a decimal separator
    float f = boost::lexical_cast<float>("1,0");
    assert(f < 1.01 && f > 0.99);
    std::locale::global(std::locale::classic()); // Restoring C locale
}



#include <algorithm>
#include <vector>
#include <iterator>
#include <boost/lexical_cast.hpp>

template <class ContainerT>
std::vector<long int> container_to_longs(const ContainerT& container) {
    typedef typename ContainerT::value_type value_type;
    std::vector<long int> ret;
    typedef long int (*func_t)(const value_type&);
    func_t f = &boost::lexical_cast<long int, value_type>;
    std::transform(container.begin(), container.end(), std::back_inserter(ret), f);
    return ret;
}

#include <set>
#include <deque>
#include <string>
#include <boost/array.hpp>

void foo5() {
    // Somewhere in source file...
    std::set<std::string> str_set;
    str_set.insert("1");
    assert(container_to_longs(str_set).front() == 1);

    std::deque<const char*> char_deque;
    char_deque.push_front("1");
    char_deque.push_back("2");
    assert(container_to_longs(char_deque).front() == 1);
    assert(container_to_longs(char_deque).back() == 2);

    // Obfuscating people with curly braces is fun!
    typedef boost::array<unsigned char, 2> element_t;
    boost::array<element_t, 2> arrays = {{ {{'1', '0'}}, {{'2', '0'}} }};
    assert(container_to_longs(arrays).front() == 10);
    assert(container_to_longs(arrays).back() == 20);
}


int main() {
    foo1();
    foo2();
    foo3();
    foo4();
    foo5();
    return 0;
}
