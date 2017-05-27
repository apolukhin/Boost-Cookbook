// Almost all the code for this recipe
// is in this header file
#include "tasks_processor_signals.hpp"
using namespace tp_full;

void accept_3_signals_and_stop(int signal) {
    static int signals_count = 0;
    assert(signal == SIGINT);

    ++ signals_count;
    std::cout << "Captured " << signals_count << " SIGINT\n"; 
    if (signals_count == 3) {
        tasks_processor::stop();
    }
}


int main () {
    tasks_processor::register_signals_handler(
        &accept_3_signals_and_stop,
        { SIGINT, SIGSEGV }
    );

    tasks_processor::start();
}
