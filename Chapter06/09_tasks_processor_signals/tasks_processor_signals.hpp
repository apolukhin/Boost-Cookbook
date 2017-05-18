#ifndef BOOK_CHAPTER6_TASK_PROCESSOR_SIGNALS_HPP
#define BOOK_CHAPTER6_TASK_PROCESSOR_SIGNALS_HPP

#include "../05_tasks_processor_multithread/tasks_processor_multithread.hpp"


#include <boost/asio/signal_set.hpp>
#include <boost/function.hpp>

namespace tp_full {

class tasks_processor: public tp_multithread::tasks_processor {
protected:
    static boost::asio::signal_set& signals() {
        static boost::asio::signal_set signals_(get());
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
        if (error) {
            std::cerr << "Error in signal handling: " << error << '\n';
        } else {
            // If signals occures while there is no waiting handlers,
            // signal notification is queued, so it won't be missed
            // while we running users_signal_handler_
            detail::make_task_wrapped(boost::bind(
                boost::ref(signal_handler()), signal_number
            ))(); // make and run task_wrapped
        }
        
        signals().async_wait(&tasks_processor::handle_signals);
    }
public:

    // This function is not threads safe!
    // Must be called before all the `start()` calls
    // Function can be called only once
    template <class Func>
    static void register_signals_handler(
            const Func& f,
            const std::vector<int>& signals_to_wait)
    {

        // Making shure that this is the first call
        assert(!signal_handler()); 

        signal_handler() = f;
        std::for_each(
            signals_to_wait.begin(),
            signals_to_wait.end(),
            boost::bind(
                &boost::asio::signal_set::add, &signals(), _1
            )
        );

        signals().async_wait(&tasks_processor::handle_signals);
    }
};

} // namespace tp_full

#endif // BOOK_CHAPTER6_TASK_PROCESSOR_SIGNALS_HPP

