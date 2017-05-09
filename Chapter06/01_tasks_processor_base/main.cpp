// Amost all the code for this example is in this header
#include "tasks_processor_base.hpp"
using namespace tp_base;

// Part of tasks_processor class from
// tasks_processor_base.hpp, that must be defined
// Somewhere in source file
tasks_processor& tasks_processor::get() {
    static tasks_processor proc;
    return proc;
}

int g_val = 0;
void func_test() {
    ++ g_val;
    if (g_val == 3) {
        throw std::logic_error("Just checking");
    }
    
    boost::this_thread::interruption_point();
    if (g_val == 10) {
        // Emulation of thread interruption.
        // Will be catched and won't stop execution.
        throw boost::thread_interrupted();
    }

    if (g_val == 90) {
        tasks_processor::get().stop();
    }
}

int main () {
    static const std::size_t tasks_count = 100;
    // stop() is called at 90
    BOOST_STATIC_ASSERT(tasks_count > 90);

    for (std::size_t i =0; i < tasks_count; ++i) {
        tasks_processor::get().push_task(&func_test);
    }

    // We can also use result of boost::bind call
    // as a task.
    tasks_processor::get().push_task(
        boost::bind(std::plus<int>(), 2, 2) // counting 2 + 2
    );

    // Processing was not started.
    assert(g_val == 0);

    // Will not throw, but blocks till
    // one of the tasks it is owning
    // calls stop().
    tasks_processor::get().start();
    assert(g_val == 90);
}
