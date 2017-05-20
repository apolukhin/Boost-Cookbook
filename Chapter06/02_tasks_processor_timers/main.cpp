// Almost all the code for this recipe
// is in this header file.
#include "tasks_processor_timers.hpp"
using namespace tp_timers;

struct test_functor {
    int& i_;

    explicit test_functor(int& i);

    void operator()() const {
        i_ = 1;
        tasks_processor::stop();
    }
};

void test_func1();

#include <boost/date_time/posix_time/posix_time.hpp>

int main () {
    const int seconds_to_wait = 3;
    int i = 0;

    tasks_processor::run_delayed(
        boost::posix_time::seconds(seconds_to_wait),
        test_functor(i)
    );

    tasks_processor::run_delayed(
        boost::posix_time::from_time_t(time(NULL) + 1),
        &test_func1
    );

    int t1 = static_cast<int>(time(NULL));
    assert(i == 0);

    // Blocks till one of the tasks
    // calls tasks_processor::stop().
    tasks_processor::start();

    assert(i == 1);
    int t2 = static_cast<int>(time(NULL));
    assert(t2 - t1 >= seconds_to_wait);
}


test_functor::test_functor(int& i)
    : i_(i)
{}

void test_func1() {
    throw std::logic_error("It works!");
}
