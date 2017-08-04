void may_throw1(char ch);
void may_throw2(const char* buffer);

void foo() {
    // we cannot allocate 10MB of memory on stack,
    // so we allocate it on heap
    char* buffer = new char[1024 * 1024 * 10];

    // Oops. Here comes some code, that may throw.
    // It was a bad idea to use raw pointer as the memory may leak!!
    may_throw1(buffer[0]);
    may_throw2(buffer);

    delete[] buffer;
}


#include <boost/scoped_array.hpp>

void foo_fixed() {
    // We allocate array on heap
    boost::scoped_array<char> buffer(new char[1024 * 1024 * 10]);

    // Here comes some code, that may throw,
    // but now exception won't cause a memory leak
    may_throw1(buffer[0]);
    may_throw2(buffer.get());

    // destructor of 'buffer' variable will call delete[]
}

#include <boost/move/make_unique.hpp>

void foo_fixed2() {
    // We allocate array on heap
    const boost::movelib::unique_ptr<char[]> buffer
        = boost::movelib::make_unique<char[]>(1024 * 1024 * 10);

    // Here comes some code, that may throw,
    // but now exception won't cause a memory leak
    may_throw1(buffer[0]);
    may_throw2(buffer.get());

    // destructor of 'buffer' variable will call delete[]
}

#include <stdexcept>
#include <cassert>

int main() {
    // foo(); // Leaks memory
    try { foo_fixed(); assert(false); } catch (...) {}
    try { foo_fixed2(); assert(false); } catch (...) {}
}


void may_throw1(char /*ch*/) {
    // Do nothing
}

void may_throw2(const char* /*buffer*/) {
    throw std::exception();
}
