#ifndef BOOK_CHAPTER6_TASK_PROCESSOR_MULTITHREAD_HPP
#define BOOK_CHAPTER6_TASK_PROCESSOR_MULTITHREAD_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "../tasks_processor_network/tasks_processor_network.hpp"

namespace tp_multithread {

class tasks_processor: public tp_network::tasks_processor {
public:
    static tasks_processor& get();

    // Default value will attempt to guess optimal count of threads
    void start_multiple(std::size_t threads_count = 0) {
        if (!threads_count) {
            threads_count = (std::max)(static_cast<int>(
                boost::thread::hardware_concurrency()), 1
            );
        }

        // one thread is the current thread
        -- threads_count;

        boost::thread_group tg;
        for (std::size_t i = 0; i < threads_count; ++i) {
            tg.create_thread(boost::bind(&boost::asio::io_service::run, boost::ref(ios_)));
        }

        ios_.run();
        tg.join_all();
    }
};

} // namespace tp_multithread

#endif // BOOK_CHAPTER6_TASK_PROCESSOR_MULTITHREAD_HPP
