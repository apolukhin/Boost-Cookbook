bool stop_parsing = true;
bool not_end_of_parsing = true;

#include <boost/thread.hpp>

void do_parse();

int main() {
    boost::thread parser_thread(&do_parse);

    // ...

    if (stop_parsing) {
        // No more parsing required.
        // TODO: Stop the parser!
    }

    if (stop_parsing) {
        // No more parsing required.
        parser_thread.interrupt();
    }

    parser_thread.join();
}

void do_parse() {
    while (not_end_of_parsing) {
        // If current thread was interrupted, the following
        // line will throw an boost::thread_interrupted.
        boost::this_thread::interruption_point();

        // Some parsing goes here.
        // ...
    }

    // Newer shall reach this code
    assert(false);
}

