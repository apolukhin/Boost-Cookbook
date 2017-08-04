class event {};

#include <boost/container/static_vector.hpp>
boost::container::static_vector<event, 5> get_events();

#include <cassert>

int main () {
    boost::container::static_vector<event, 5> ev = get_events();
    assert(ev.size() == 5);

    boost::container::static_vector<int, 2> ints;
    ints.push_back(1);
    ints.push_back(2);
    try {
        // The following line always throws:
        ints.push_back(3);
    } catch (const std::bad_alloc& ) {
        // ...
    }
}


boost::container::static_vector<event, 5> get_events() {
    boost::container::static_vector<event, 5> ev;
    for (unsigned i = 0; i < 5; ++i) {
        ev.emplace_back();
    }
    return ev;
}

/*

#include <vector>
std::vector<event> get_events();

#include <boost/array.hpp>
boost::array<event, 5> get_events();

#include <boost/container/small_vector.hpp>
boost::container::small_vector<event, 5> get_events();

*/
