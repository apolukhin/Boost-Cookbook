#include <iostream>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/atomic.hpp>

typedef boost::atomic<int> atomic_t;
#if (BOOST_ATOMIC_INT_LOCK_FREE != 2)
#error "This code requires lock-free boost::atomic<int>"
#endif

//#include <atomic>
//typedef std::atomic<int> atomic_t;



int main() {
    boost::interprocess::managed_shared_memory 
        segment(boost::interprocess::open_or_create, "shm1-cache", 1024);

    atomic_t& atomic 
        = *segment.find_or_construct<atomic_t> // 1
            ("shm1-counter")                   // 2
            (0)                                // 3
    ;

    std::cout << "I have index " << ++ atomic 
        << ". Press any key...\n";
    std::cin.get();

    const int snapshot = --atomic;
    if (!snapshot) {
        segment.destroy<atomic_t>("shm1-counter");
        boost::interprocess::shared_memory_object
                ::remove("shm1-cache");
    }
} /*main*/
