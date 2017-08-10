void do_assert(int threads_joined);



#include <boost/thread.hpp>

void some_function();

void sample() {
    boost::thread t1(&some_function);
    boost::thread t2(&some_function);
    boost::thread t3(&some_function);
    // ...

    t1.join();
    t2.join();
    t3.join();
}



#include <boost/thread.hpp>

int main() {
    boost::thread_group threads;

    // Launching 10 threads.
    for (unsigned i = 0; i < 10; ++i) {
        threads.create_thread(&some_function);
    }

    // Joining all threads.
    threads.join_all();

    // We can also interrupt all of them
    // by calling threads.interrupt_all();

    do_assert(10);
    sample();
    do_assert(13);
}


// details:

#include <boost/atomic.hpp>
boost::atomic_int g_counter(0);

void do_assert(int threads_joined) {
    assert(g_counter == threads_joined);
}

void some_function() {
    ++g_counter;
}
