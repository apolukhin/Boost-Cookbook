#include <cassert>
#include <boost/atomic.hpp>
boost::atomic_int g_counter(0);
void some_function(){ ++ g_counter; }

#include <boost/thread.hpp>
int main() {
    boost::thread t1(&some_function);
    boost::thread t2(&some_function);
    boost::thread t3(&some_function);
    // ...

    t1.join();
    t2.join();
    t3.join();

    assert(g_counter == 3);

    // Launching 10 threads
    boost::thread_group threads;
    for (unsigned i = 0; i < 10; ++i) {
        threads.create_thread(&some_function);
    }

    // Joining all threads
    threads.join_all();

    // We can also interrupt all of them
    // by calling threads.interrupt_all();

    assert(g_counter == 13);
}
