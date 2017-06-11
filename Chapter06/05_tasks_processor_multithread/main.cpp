// See this header some code of this recipe
#include "tasks_processor_multithread.hpp"
using namespace tp_multithread;

const std::size_t threads_count = 5;
#include <boost/thread/barrier.hpp>
boost::barrier g_barrier(threads_count);

void multythread_test() {
    g_barrier.wait();
    tasks_processor::stop();
}

int main() {
    for (std::size_t i = 0; i < threads_count; ++i) {
        tasks_processor::push_task(&multythread_test);
    }
    tasks_processor::start_multiple(threads_count);

    tasks_processor::start_multiple();
    tasks_processor::stop();
}
