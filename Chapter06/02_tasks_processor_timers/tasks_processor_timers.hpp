#ifndef BOOK_CHAPTER6_TASK_PROCESSOR_TIMERS_HPP
#define BOOK_CHAPTER6_TASK_PROCESSOR_TIMERS_HPP

#include "../01_tasks_processor_base/tasks_processor_base.hpp"

#include <boost/asio/io_service.hpp>
#include <boost/asio/deadline_timer.hpp>
#include <boost/system/error_code.hpp>
#include <boost/make_shared.hpp>
#include <iostream>

namespace detail {

    template <class Functor>
    struct timer_task {
    private:
        boost::shared_ptr<boost::asio::deadline_timer> timer_;
        task_wrapped<Functor> task_;

    public:
        explicit timer_task(
                boost::shared_ptr<boost::asio::deadline_timer> timer,
                const Functor& task_unwrapped)
            : timer_(boost::move(timer))
            , task_(task_unwrapped)
        {}

        void operator()(const boost::system::error_code& error) const {
            if (!error) {
                task_();
            } else {
                std::cerr << error << '\n';
            }
        }
    };
} // namespace detail

namespace tp_timers {

class tasks_processor: public tp_base::tasks_processor {
public:

    template <class Time, class Functor>
    static void run_delayed(Time duration_or_time, const Functor& f) {
        boost::shared_ptr<boost::asio::deadline_timer> timer(
            boost::make_shared<boost::asio::deadline_timer>(
                boost::ref(get()), duration_or_time
            )
        );

        boost::asio::deadline_timer& timer_ref = *timer;

        timer_ref.async_wait(
            detail::timer_task<Functor>(
                boost::move(timer),
                f
            )
        );
    }
};

} // namespace tp_timers

#endif // BOOK_CHAPTER6_TASK_PROCESSOR_TIMERS_HPP
