#ifndef BOOK_CHAPTER6_TASK_PROCESSOR_TIMERS_HPP
#define BOOK_CHAPTER6_TASK_PROCESSOR_TIMERS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "../tasks_processor_base/tasks_processor_base.hpp"

#include <boost/asio/io_service.hpp>
#include <boost/asio/deadline_timer.hpp>
#include <boost/system/error_code.hpp>
#include <boost/make_shared.hpp>
#include <iostream>

namespace detail {
    typedef boost::asio::deadline_timer::duration_type duration_type;

    template <class Functor>
    struct timer_task: public task_wrapped<Functor> {
    private:
        typedef task_wrapped<Functor> base_t;
        boost::shared_ptr<boost::asio::deadline_timer> timer_;

    public:
        template <class Time>
        explicit timer_task(
                boost::asio::io_service& ios,
                const Time& duration_or_time,
                const Functor& task_unwrapped)
            : base_t(task_unwrapped)
            , timer_(boost::make_shared<boost::asio::deadline_timer>(
                boost::ref(ios), duration_or_time
            ))
        {}

        void push_task() const {
            timer_->async_wait(*this);
        }

        void operator()(const boost::system::error_code& error) const {
            if (!error) {
                base_t::operator()();
            } else {
                std::cerr << error << '\n';
            }
        }
    };
} // namespace detail

namespace detail {
    template <class Time, class Functor>
    inline timer_task<Functor> make_timer_task(
        boost::asio::io_service& ios,
        const Time& duration_or_time,
        const Functor& task_unwrapped)
    {
        return timer_task<Functor>(ios, duration_or_time, task_unwrapped);
    }
}

namespace tp_timers {

class tasks_processor: public tp_base::tasks_processor {
public:
    static tasks_processor& get();

    typedef boost::asio::deadline_timer::duration_type duration_type;

    template <class Functor>
    void run_after(duration_type duration, const Functor& f) {
        detail::make_timer_task(ios_, duration, f)
            .push_task();
    }
    
    typedef boost::asio::deadline_timer::time_type time_type;

    template <class Functor>
    void run_at(time_type time, const Functor& f) {
        detail::make_timer_task(ios_, time, f)
            .push_task();
    }
};

} // namespace tp_timers

#endif // BOOK_CHAPTER6_TASK_PROCESSOR_TIMERS_HPP
