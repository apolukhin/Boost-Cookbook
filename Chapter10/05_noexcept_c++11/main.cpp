#include <boost/config.hpp>

class move_nothrow {
    // Some class class members go here.
    // ...

public:
    move_nothrow() BOOST_NOEXCEPT;
    move_nothrow(move_nothrow&&) BOOST_NOEXCEPT
        // Members initialization goes here.
        // ...
    {}

    move_nothrow& operator=(move_nothrow&&) BOOST_NOEXCEPT {
        // Implementation goes here.
        // ...
        return *this;
    }

    move_nothrow(const move_nothrow&);
    move_nothrow& operator=(const move_nothrow&);
};

// In header file.
int foo() BOOST_NOEXCEPT;


// In source file.
int foo() BOOST_NOEXCEPT {
    return 0;
}

#include <vector>

int main() {
    std::vector<move_nothrow> v(10);
    v.push_back(move_nothrow());

    foo();
}


// details:
move_nothrow::move_nothrow() BOOST_NOEXCEPT {}
