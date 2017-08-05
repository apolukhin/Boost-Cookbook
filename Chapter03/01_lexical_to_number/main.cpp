#include <sstream>

void sample1() {
    std::istringstream iss("100");
    int i;
    iss >> i;

    // ...
}



#include <cstdlib>

void sample2() {
    char * end;
    const int i = std::strtol ("100", &end, 10);

    // ...
    (void)i; // Supressing warning about unused variable.
}



#include <boost/lexical_cast.hpp>

void sample3() {
    const int i = boost::lexical_cast<int>("100");
    // ...
    (void)i; // Supressing warning about unused variable.
}



#include <boost/lexical_cast.hpp>

void sample4() {
    char chars[] = {'x', '1', '0', '0', 'y' }; 
    const int i = boost::lexical_cast<int>(chars + 1, 3); 
    assert(i == 100); 
}



#include <boost/lexical_cast.hpp>
#include <iostream>

void sample5() {
    try {
        // short usually may not store values greater than 32767
        const short s = boost::lexical_cast<short>("1000000");
        assert(false); // Must not reach this line.
        (void)s; // Supressing warning about unused variable.
    } catch (const boost::bad_lexical_cast& e) {
        std::cout << e.what() << '\n';
    }
}



#include <boost/lexical_cast.hpp>
#include <iostream>

void sample6() {
    try {
        const int i = boost::lexical_cast<int>("This is not a number!");
        assert(false); // Must not reach this line.
        (void)i; // Supressing warning about unused variable.
    } catch (const boost::bad_lexical_cast& /*e*/) {}
}



#include <boost/lexical_cast.hpp>
#include <cassert>

void sample7() {
    int i = 0;
    const bool ok = boost::conversion::try_lexical_convert("Bad stuff", i);
    assert(!ok);
}



#include <boost/lexical_cast.hpp>
#include <locale>

void sample8() {
    try {
        std::locale::global(std::locale("ru_RU.UTF8"));
        // In Russia coma sign is used as a decimal separator.
        float f = boost::lexical_cast<float>("1,0");
        assert(f < 1.01 && f > 0.99);
        std::locale::global(std::locale::classic()); // Restoring C locale
    } catch (const std::runtime_error&) { /* locale is not supported */ }
}


int main() {
    sample1();
    sample2();
    sample3();
    sample4();
    sample5();
    sample6();
    sample7();
    sample8();
}
