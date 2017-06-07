#include "../06_A_my_library/my_library.hpp"
#include <cassert>

int main() {
    assert(foo() == 0);
    bar b;
    try {
        b.meow();
        assert(false);
    } catch (const bar_exception&) {}
}
