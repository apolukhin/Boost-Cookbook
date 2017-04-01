
void may_throw1(const char* buffer);
void may_throw2(const char* buffer);

void foo() {
    // we can not allocate 10MB of memory on stack,
    // so we allocate it on heap
    char* buffer = new char[1024 * 1024 * 10];

    // Here comes some code, that may throw
    may_throw1(buffer);
    may_throw2(buffer);

    delete[] buffer;
}

#include <boost/scoped_array.hpp>

void foo_fixed() {
    // so we allocate it on heap
    boost::scoped_array<char> buffer(new char[1024 * 1024 * 10]);

    // Here comes some code, that may throw,
    // but now exception won't couse a memory leak
    may_throw1(buffer.get());
    may_throw2(buffer.get());

    // destructor of 'buffer' variable will call delete[]
}

#include <stdexcept>
#include <assert.h>

int main() {
    // foo(); // Leaks memory
    try {
        foo_fixed();
    } catch (...){}

    return 0;
}


void may_throw1(const char* /*buffer*/) {
    // Do nothing
}

void may_throw2(const char* /*buffer*/) {
    throw std::exception();
}
