#ifndef BOOK_CHAPTER6_TASK_PROCESSOR_SIGNALS_HPP
#define BOOK_CHAPTER6_TASK_PROCESSOR_SIGNALS_HPP

#include "../05_tasks_processor_multithread/tasks_processor_multithread.hpp"


#include <boost/asio/signal_set.hpp>
#include <boost/function.hpp>

namespace tp_full {

class tasks_processor: public tp_multithread::tasks_processor {
protected:
    static boost::asio::signal_set& signals() {
        static boost::asio::signal_set signals_(get_ios());
        return signals_;
    }

    static boost::function<void(int)>& signal_handler() {
        static boost::function<void(int)> users_signal_handler_;
        return users_signal_handler_;
    }

private:
    static void handle_signals(
            const boost::system::error_code& error,
            int signal_number)
    {
        signals().async_wait(&tasks_processor::handle_signals);

        if (error) {
            std::cerr << "Error in signal handling: " << error << '\n';
        } else {
            boost::function<void(int)> h = signal_handler();

            detail::make_task_wrapped([h, signal_number]() {
                h(signal_number);
            })(); // make and run task_wrapped
        }

    }

public:
    // This function is not thread safe!
    // Must be called before all the `start()` calls.
    // Function can be called only once.
    template <class Func>
    static void register_signals_handler(
            const Func& f,
            std::initializer_list<int> signals_to_wait)
    {
        // Making shure that this is the first call.
        assert(!signal_handler()); 

        signal_handler() = f;
        boost::asio::signal_set& sigs = signals();
        
        std::for_each(
            signals_to_wait.begin(),
            signals_to_wait.end(),
            [&sigs](int signal) { sigs.add(signal); }
        );

        sigs.async_wait(&tasks_processor::handle_signals);
    }
};

} // namespace tp_full

#endif // BOOK_CHAPTER6_TASK_PROCESSOR_SIGNALS_HPP

