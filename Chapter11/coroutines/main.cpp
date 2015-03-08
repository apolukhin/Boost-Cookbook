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

#include <boost/version.hpp>

// Coroutines changed interface in Boost 1.56
#if BOOST_VERSION < 105600

#include <boost/coroutine/coroutine.hpp>

typedef boost::coroutines::coroutine< 
    std::string&(std::size_t max_characters_to_process) 
> corout_t;

void coroutine_task(corout_t::caller_type& caller) {
    std::string result;
    // Returning back to main programm
    caller(result);

    while (1) {
        std::size_t max_characters_to_process = caller.get();

        // Do process some characters
        // ...
        result.resize(result.size() + max_characters_to_process);

        // Returning result, switching back
        // to main program
        caller(result);
    } /*while*/
}

void coroutine_task(corout_t::caller_type& caller);

int main() {
    corout_t coroutine(coroutine_task);

    // Doing some work
    // ...
    spinlock_t spinlock;
    port_t port;
    
    while (!spinlock.try_lock()) {
        // We may do some usefull work, before 
        // attempting to lock a spinlock once more
        coroutine(10); // Small delays
    }
    // Spinlock is locked
    // ...
    assert(coroutine.get().size() == 10 * 100);
    coroutine.get().clear();

    while (!port.block_ready()) {
        // We may do some usefull work, before 
        // attempting to get block of data once more
        coroutine(300);  // Bigger delays
        std::string& s = coroutine.get();
        // ...
        (void)s;
    }

    assert(coroutine.get().size() == 10 * 300);
}

#else

#include <boost/coroutine/coroutine.hpp>

typedef boost::coroutines::asymmetric_coroutine<std::size_t> corout_t;

struct coroutine_task {
    std::string& result;

    explicit coroutine_task(std::string& result_in)
        : result(result_in)
    {}

    void operator()(corout_t::pull_type& yield) {
        while (1) {
            std::size_t max_characters_to_process = yield.get();

            // Do process some characters
            // ...
            result.resize(result.size() + max_characters_to_process);

            // Returning result, switching back
            // to main program
            yield();
        } /*while*/
    }
};

int main() {
    std::string result;
    coroutine_task task(result);
    corout_t::push_type coroutine(task);

    // Doing some work
    // ...
    spinlock_t spinlock;
    port_t port;

    while (!spinlock.try_lock()) {
        // We may do some usefull work, before
        // attempting to lock a spinlock once more
        coroutine(10); // Small delays
    }
    // Spinlock is locked
    // ...
    assert(result.size() == 10 * 100);
    result.clear();

    while (!port.block_ready()) {
        // We may do some usefull work, before
        // attempting to get block of data once more
        coroutine(300);  // Bigger delays
        // Do something with `result` variable
    }

    assert(result.size() == 10 * 300);
}

#endif // BOOST_VERSION < 105600
