#include <cstddef> // for std::size_t

bool is_first_run();

// Function that executes for a long time.
void fill_file(char fill_char, std::size_t size, const char* filename);

// Called in thread that draws a user interface:
void example_without_threads() {
    if (is_first_run()) {
        // This will be executing for a long time during which
        // users interface freezes...
        fill_file(0, 8 * 1024 * 1024, "save_file.txt");
    }
}




#include <boost/thread.hpp>

// Called in thread that draws a user interface:
void example_with_threads() {
    if (is_first_run()) {
        boost::thread(boost::bind(
            &fill_file,
            0,
            8 * 1024 * 1024,
            "save_file.txt"
        )).detach();
    }
}



void example_with_joining_threads() {
    if (is_first_run()) {
        boost::thread t(boost::bind(
            &fill_file,
            0,
            8 * 1024 * 1024,
            "save_file.txt"
        ));

        // Do some work.
        // ...

        // Waiting for thread to finish.
        t.join();
    }
}



#include <boost/thread/scoped_thread.hpp>

void some_func();

void example_with_raii() {
    boost::scoped_thread<boost::join_if_joinable> t(
        boost::thread(&some_func)
    );

    // 't' will be joined at scope exit.
}



void set_not_first_run();

int main() {
    example_with_threads();
    example_with_joining_threads();
    example_with_raii();

    example_without_threads();
}

// details:

#include <algorithm>
#include <fstream>
#include <iterator>
void fill_file(char fill_char, std::size_t size, const char* filename) {
    std::ofstream ofs(filename);
    std::fill_n(std::ostreambuf_iterator<char>(ofs), size, fill_char);
    set_not_first_run();
}

static bool g_is_first_run = true;
void set_not_first_run() {
    g_is_first_run = false;
}

bool is_first_run() {
    return g_is_first_run;
}

void some_func(){}
