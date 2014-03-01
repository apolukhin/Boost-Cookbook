#ifndef BOOK_CHAPTER6_TASK_PROCESSOR_SIGNALS_HPP
#define BOOK_CHAPTER6_TASK_PROCESSOR_SIGNALS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "../tasks_processor_multithread/tasks_processor_multithread.hpp"


#include <boost/asio/signal_set.hpp>
#include <boost/function.hpp>

namespace tp_full {

class tasks_processor: public tp_multithread::tasks_processor {
/*
    tasks_processor()
        : ios_()
        , work_(ios_)
        , signals_(ios_)
    {}
*/

    tasks_processor()
        : tp_multithread::tasks_processor()
        , signals_(ios_)
    {}


public:
    static tasks_processor& get();

private:
    boost::asio::signal_set signals_;
    boost::function<void(int)>   users_signal_handler_;
    
    // private
    void handle_signals(
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
                boost::ref(users_signal_handler_), signal_number
            ))(); // make and run task_wrapped
        }
        
        signals_.async_wait(boost::bind(
            &tasks_processor::handle_signals, this, _1, _2
        ));
    }
public:

    // This function is not threads safe!
    // Must be called before all the `start()` calls
    // Function can be called only once
    template <class Func>
    void register_signals_handler(
            const Func& f,
            const std::vector<int>& signals_to_wait)
    {
        // Making shure that this is the first call
        assert(!users_signal_handler_); 

        users_signal_handler_ = f;
        std::for_each(
            signals_to_wait.begin(),
            signals_to_wait.end(),
            boost::bind(
                &boost::asio::signal_set::add, &signals_, _1
            )
        );

        signals_.async_wait(boost::bind(
            &tasks_processor::handle_signals, this, _1, _2
        ));
    }
};

} // namespace tp_full

#endif // BOOK_CHAPTER6_TASK_PROCESSOR_SIGNALS_HPP

