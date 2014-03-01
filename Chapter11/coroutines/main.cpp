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
