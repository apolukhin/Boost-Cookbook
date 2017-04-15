#include <cassert>
#include <cstddef>

// In previous recipe we included
// <boost/thread.hpp>, which includes all
// the classes of Boost.Thread
#include <boost/thread/thread.hpp>

namespace without_sync {

int shared_i = 0;

void do_inc() {
    for (std::size_t i = 0; i < 30000; ++i) {
        // do some work
        // ...
        int i_snapshot = ++ shared_i;

        // do some work with i_snapshot
        // ...
        (void) i_snapshot;
    }
}

void do_dec() {
    for (std::size_t i = 0; i < 30000; ++i) {
        // do some work
        // ...
        int i_snapshot = -- shared_i;

        // do some work with i_snapshot
        // ...
        (void) i_snapshot;
    }
}

void run() {
    boost::thread t1(&do_inc);
    boost::thread t2(&do_dec);

    t1.join();
    t2.join();

    // assert(global_i == 0); // Oops!
    std::cout << "shared_i == " << shared_i;
}

} // namespace without_sync

#include <boost/thread/mutex.hpp>
#include <boost/thread/locks.hpp>

namespace with_sync {

int shared_i = 0;
boost::mutex i_mutex;

void do_inc() {
    for (std::size_t i = 0; i < 30000; ++i) {
        // do some work
        // ...
        int i_snapshot;
        { // Critical section begin
            boost::lock_guard<boost::mutex> lock(i_mutex);
            i_snapshot = ++ shared_i;
        } // Critical section end

        // do some work with i_snapshot
        // ...
        (void)i_snapshot;
    }
}

void do_dec() {
    for (std::size_t i = 0; i < 30000; ++i) {
        // do some work
        // ...
        int i_snapshot;
        { // Critical section begin
            boost::lock_guard<boost::mutex> lock(i_mutex);
            i_snapshot = -- shared_i;
        } // Critical section end

        // do some work with i_snapshot
        // ...
        (void) i_snapshot;
    }
}

void run() {
    boost::thread t1(&do_inc);
    boost::thread t2(&do_dec);

    t1.join();
    t2.join();

    assert(shared_i == 0);
    std::cout << "shared_i == " << shared_i;
}

} // namespace without_sync

#include <boost/thread/recursive_mutex.hpp>

int main() {
    without_sync::run();
    std::cout << '\n';
    with_sync::run();
    std::cout << '\n';
}
