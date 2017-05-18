// Amost all the code for this example is in this header
#include "tasks_processor_base.hpp"
using namespace tp_base;

int func_test() {
    static int counter = 0;
    ++ counter;
    boost::this_thread::interruption_point();

    switch (counter) {
    case 3:
        throw std::logic_error("Just checking");

    case 10:
        // Emulation of thread interruption.
        // Must be caught and must not stop execution.
        throw boost::thread_interrupted();

    case 90:
        // Stopping the tasks_processor.
        tasks_processor::stop();
    }

    return counter;
}

int main () {
    static const std::size_t tasks_count = 100;
    // stop() is called at 90
    BOOST_STATIC_ASSERT(tasks_count > 90);

    for (std::size_t i =0; i < tasks_count; ++i) {
        tasks_processor::push_task(&func_test);
    }

    // We can also use result of boost::bind call
    // as a task.
    tasks_processor::push_task(
        boost::bind(std::plus<int>(), 2, 2) // counting 2 + 2
    );

    // Processing was not started.
    assert(func_test() == 1);

    // Will not throw, but blocks till
    // one of the tasks it is owning
    // calls stop().
    tasks_processor::start();
    assert(func_test() == 91);
}
