
// Almost all the code for this recipe
// is in this header file
#include "tasks_processor_timers.hpp"
using namespace tp_timers;


// Part of tasks_processor class from
// tasks_processor_timers.hpp, that must be defined
// Somewhere in source file
tasks_processor& tasks_processor::get() {
    static tasks_processor proc;
    return proc;
}

void test_func(int& i) {
    i = 1;
    tasks_processor::get().stop();
}

void test_func1() {
    throw std::logic_error("It works!");
}

#include <boost/date_time/posix_time/posix_time.hpp>

int main () {
    const int seconds_to_wait = 3;
    int i = 0;

    tasks_processor::get().run_after(
        boost::posix_time::seconds(seconds_to_wait),
        boost::bind(&test_func, boost::ref(i))
    );
        
    tasks_processor::get().run_at(boost::posix_time::from_time_t(time(NULL) + 1), &test_func1);

    int t1 = static_cast<int>(time(NULL));
    assert(i == 0);

    tasks_processor::get().start();
    assert(i == 1);
    int t2 = static_cast<int>(time(NULL));
    assert(t2 - t1 >= seconds_to_wait); // seconds_to_wait seconds elapsed
}
