#include <boost/container/flat_set.hpp>
#include <algorithm>
#include <cassert>

int main() {
    boost::container::flat_set<int> set;
    set.reserve(4096);

    for (int i = 0; i < 4000; ++i) {
        set.insert(i);
    }

    // 5.1
    assert(set.lower_bound(500) - set.lower_bound(100) == 400);

    // 5.2
    set.erase(0);

    // 5.3
    set.erase(5000);

    // 5.4
    assert(std::lower_bound(set.cbegin(), set.cend(), 900000) == set.cend());

    // 5.5
    assert(
        set.lower_bound(100) + 400 
        == 
        set.find(500)
    );
} // end of main() function

