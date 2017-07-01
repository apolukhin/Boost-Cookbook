#include <iostream>

struct spinlock_t {
    bool try_lock() {
        static int i = 0;
        return i++ >= 100;
    }
};

struct port_t {
    bool block_ready() {
        static int i = 0;
        return i++ >= 10;
    }
};


#include <boost/coroutine2/coroutine.hpp>

typedef boost::coroutines2::asymmetric_coroutine<std::size_t> corout_t;

struct coroutine_task {
    std::string& result;

    explicit coroutine_task(std::string& result_in)
        : result(result_in)
    {}

    void operator()(corout_t::pull_type& yield) {
        while (1) {
            std::size_t max_characters_to_process = yield.get();

            // Do process some characters.
            // ...
            result.resize(result.size() + max_characters_to_process);

            // Returning result, switching back
            // to main program.
            yield();
        } /*while*/
    }
};

int main() {
    std::string result;
    coroutine_task task(result);
    corout_t::push_type coroutine(task);

    // Doing some work.
    // ...
    spinlock_t spinlock;
    port_t port;

    while (!spinlock.try_lock()) {
        // We may do some usefull work, before
        // attempting to lock a spinlock once more.
        coroutine(10); // Small delays.
    }
    // Spinlock is locked.
    // ...
    assert(result.size() == 10 * 100);
    result.clear();

    while (!port.block_ready()) {
        // We may do some usefull work, before
        // attempting to get block of data once more.
        coroutine(300);  // Bigger delays.
        // Do something with `result` variable.
    }

    assert(result.size() == 10 * 300);

    std::cout << "OK\n";
}
