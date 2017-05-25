#ifndef BOOK_CHAPTER6_TASK_PROCESSOR_MULTITHREAD_HPP
#define BOOK_CHAPTER6_TASK_PROCESSOR_MULTITHREAD_HPP

#include "../04_tasks_processor_network_accept/tasks_processor_network_accept.hpp"

#include <boost/thread.hpp>

namespace tp_multithread {

class tasks_processor: public tp_network::tasks_processor {
public:
    // Default value will attempt to guess optimal count of threads.
    static void start_multiple(std::size_t threads_count = 0) {
        if (!threads_count) {
            threads_count = (std::max)(static_cast<int>(
                boost::thread::hardware_concurrency()), 1
            );
        }

        // First thread is the current thread.
        -- threads_count;

        boost::asio::io_service& ios = get_ios();
        boost::thread_group tg;
        for (std::size_t i = 0; i < threads_count; ++i) {
            tg.create_thread([&ios]() { ios.run(); });
        }

        ios.run();
        tg.join_all();
    }
};

} // namespace tp_multithread

#endif // BOOK_CHAPTER6_TASK_PROCESSOR_MULTITHREAD_HPP
