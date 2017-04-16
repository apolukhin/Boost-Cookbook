#include <sstream>

void foo1() {
    std::istringstream iss("100");
    int i;
    iss >> i;
}

#include <cstdlib>
void foo2() {
    char * end;
    const int i = std::strtol ("100", &end, 10);

    (void)i; // Supressing warning about unused variable
}

#include <boost/lexical_cast.hpp>

void foo3() {
    {
    const int i = boost::lexical_cast<int>("100");
    (void)i; // Supressing warning about unused variable
    }

    {
    char chars[] = {'1', '0', '0' };
    const int i = boost::lexical_cast<int>(chars, 3);
    assert(i == 100);
    }


    try {
        // short usually may not store values greater than 32767
        const short s = boost::lexical_cast<short>("1000000");
        assert(false); // Must not reach this
        (void)s; // Supressing warning about unused variable
    } catch (const boost::bad_lexical_cast& /*e*/) {}


    try {
        const int i = boost::lexical_cast<int>("This is not a number!");
        assert(false); // Must not reach this
        (void)i; // Supressing warning about unused variable
    } catch (const boost::bad_lexical_cast& /*e*/) {}

    {
    int i = 0;
    const bool ok = boost::conversion::try_lexical_convert("Bad stuff", i);
    assert(!ok);
    }
}

#include <locale>
void foo4() {
    std::locale::global(std::locale("ru_RU.UTF8"));
    // In Russia coma sign is used as a decimal separator.
    float f = boost::lexical_cast<float>("1,0");
    assert(f < 1.01 && f > 0.99);
    std::locale::global(std::locale::classic()); // Restoring C locale
}


int main() {
    foo1();
    foo2();
    foo3();
    foo4();
}
