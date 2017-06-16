
#include <boost/thread/thread.hpp>
#include <iostream>

namespace detail {

template <class T>
struct task_wrapped {
private:
    T task_unwrapped_;

public:
    explicit task_wrapped(const T& f)
        : task_unwrapped_(f)
    {}

    void operator()() const {
        // Resetting interruption.
        try {
            boost::this_thread::interruption_point();
        } catch(const boost::thread_interrupted&){}

        try {
            // Executing task.
            task_unwrapped_();
        } catch (const std::exception& e) {
            std::cerr<< "Exception: " << e.what() << '\n';
        } catch (const boost::thread_interrupted&) {
            std::cerr<< "Thread interrupted\n";
        } catch (...) {
            std::cerr<< "Unknown exception\n";
        }
    }
};

} // namespace detail

namespace detail {

template <class T>
task_wrapped<T> make_task_wrapped(const T& task_unwrapped) {
    return task_wrapped<T>(task_unwrapped);
}

} // namespace detail


#include <boost/asio/io_service.hpp>
namespace tp_base {

class tasks_processor: private boost::noncopyable {
protected:
    static boost::asio::io_service& get_ios() {
        static boost::asio::io_service ios;
        static boost::asio::io_service::work work(ios);

        return ios;
    }

public:
    template <class T>
    static void push_task(const T& task_unwrapped) {
        get_ios().post(detail::make_task_wrapped(task_unwrapped));
    }

    static void start() {
        get_ios().run();
    }

    static void stop() {
        get_ios().stop();
    }
}; // tasks_processor

} // namespace tp_base

using namespace tp_base;

#include <boost/exception_ptr.hpp>

struct process_exception {
    boost::exception_ptr exc_;

    explicit process_exception(const boost::exception_ptr& exc)
        : exc_(exc)
    {}

    void operator()() const;
};

#include <boost/lexical_cast.hpp>
void func_test2(); // Forward declaration.

void process_exception::operator()() const  {
    try {
        boost::rethrow_exception(exc_);
    } catch (const boost::bad_lexical_cast& /*e*/) {
        std::cout << "Lexical cast exception detected.\n" << std::endl;

        // Pushing another task to execute.
        tasks_processor::push_task(&func_test2);
    } catch (...) {
        std::cout << "Can not handle such exceptions:\n" 
            << boost::current_exception_diagnostic_information() 
            << std::endl;

        // Stopping.
        tasks_processor::stop();
    }
}

#include <stdexcept>
void func_test1() {
    try {
        boost::lexical_cast<int>("oops!");
    } catch (...) {
        tasks_processor::push_task(
            process_exception(boost::current_exception())
        );
    }
}

void func_test2() {
    try {
        // ...
        BOOST_THROW_EXCEPTION(std::logic_error("Some fatal logic error"));
        // ...
    } catch (...) {
        tasks_processor::push_task(
            process_exception(boost::current_exception())
        );
    }
}

void run_throw(boost::exception_ptr& ptr) {
    try {
        // A lot of code goes here.
    } catch (...) {
        ptr = boost::current_exception();
    }
}

int main () {
    tasks_processor::push_task(&func_test1);
    tasks_processor::start();


    boost::exception_ptr ptr;

    // Do some work in parallel.
    boost::thread t(
        &run_throw,
        boost::ref(ptr)
    );

    // Some code goes here.
    // ...

    t.join();

    // Checking for exception.
    if (ptr) {
        // Exception occurred in thread.
        boost::rethrow_exception(ptr);
    }
}
