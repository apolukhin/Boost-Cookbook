#include <boost/noncopyable.hpp>

class connection: boost::noncopyable {
public:
    // Opening a connection is a slow operation
    void open();

    void send_result(int result);

    // Other methods
    // ...
    int open_count_;
    connection(): open_count_(0) {}
};

// In header file:
connection& get_connection();

// In source file:
#include <boost/thread/tss.hpp>
boost::thread_specific_ptr<connection> connection_ptr;

connection& get_connection() {
    connection* p = connection_ptr.get();
    if (!p) {
        connection_ptr.reset(new connection);
        p = connection_ptr.get();
        p->open();
    }

    return *p;
}


void task() {
    int result = 2;
    // Some computations go there.
    // ...

    // Sending the result:
    get_connection().send_result(result);
}

void connection::open() {
    assert(!open_count_);
    open_count_ = 1;
}

void connection::send_result(int /*result*/) {}

void run_tasks() {
    for (std::size_t i = 0; i < 1000 /*0000*/; ++i) {
        task();
    }
}

#include <boost/thread/thread.hpp>

int main() {
    boost::thread t1(&run_tasks);
    boost::thread t2(&run_tasks);
    boost::thread t3(&run_tasks);
    boost::thread t4(&run_tasks);

    // Waiting for all the tasks to stop.
    t1.join();
    t2.join();
    t3.join();
    t4.join();
}
