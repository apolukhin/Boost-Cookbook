#include <iostream>
#include <boost/interprocess/managed_shared_memory.hpp>

#include <boost/interprocess/containers/deque.hpp>
#include <boost/interprocess/allocators/allocator.hpp>

#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/sync/interprocess_condition.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>

#include <boost/optional.hpp>

struct task_structure {
    // ...
    std::size_t value_;
};

class work_queue {
public:
    typedef task_structure task_type;
    typedef boost::interprocess::managed_shared_memory
        managed_shared_memory_t;

    typedef boost::interprocess::allocator<
        task_type, 
        managed_shared_memory_t::segment_manager
    > allocator_t;

private:
    managed_shared_memory_t segment_;
    const allocator_t allocator_;

    typedef boost::interprocess::deque<task_type, allocator_t>
        deque_t;

    typedef boost::interprocess::interprocess_mutex mutex_t;
    typedef boost::interprocess::interprocess_condition
        condition_t;
    typedef boost::interprocess::scoped_lock<mutex_t>
        scoped_lock_t;

    deque_t& tasks_;
    mutex_t& mutex_;
    boost::interprocess::interprocess_condition& cond_;

public:
    explicit work_queue()
        : segment_(
              boost::interprocess::open_or_create,
              "work-queue",
              1024 * 1024 * 32
        )
        , allocator_(segment_.get_segment_manager())
        , tasks_(
            *segment_.find_or_construct<deque_t>
              ("work-queue:deque")(allocator_)
        )
        , mutex_(
            *segment_.find_or_construct<mutex_t>
              ("work-queue:mutex")()
        )
        , cond_(
            *segment_.find_or_construct<condition_t>
              ("work-queue:condition")()
        )
    {}

    void cleanup() {
        segment_.destroy<condition_t>("work-queue:condition");
        segment_.destroy<mutex_t>("work-queue:mutex");
        segment_.destroy<deque_t>("work-queue:deque");

        boost::interprocess::shared_memory_object
            ::remove("work-queue");
    }

    void push_task(const task_type& task) {
        {
            scoped_lock_t lock(mutex_);
            tasks_.push_back(task);
        }
        cond_.notify_one();
    }

    boost::optional<task_type> try_pop_task() {
        boost::optional<task_type> ret;
        scoped_lock_t lock(mutex_);
        if (!tasks_.empty()) {
            ret = tasks_.front();
            tasks_.pop_front();
        }

        return ret;
    }

    task_type pop_task() {
        scoped_lock_t lock(mutex_);
        while (tasks_.empty()) {
            cond_.wait(lock);
        }

        task_type ret = tasks_.front();
        tasks_.pop_front();

        return ret;
    }
};


int main() {
    try {
        static const std::size_t max_tasks_count = 10000;
        work_queue queue;

        boost::optional<task_structure> task = queue.try_pop_task();
        if (!task) {
            std::cout << "Filling data" << std::endl;
            task_structure ts;
            for (std::size_t i = 0; i < max_tasks_count; ++i) {
                ts.value_ = i;
                queue.push_task(ts);
            }
        } else {
            std::cout << "Gettinging data" << std::endl;
            assert(task->value_ == 0);
            for (std::size_t i = 1; i < max_tasks_count; ++i) {
                assert(queue.pop_task().value_ == i);
            }

            assert(!queue.try_pop_task());

            queue.cleanup();
        }
    } catch (const std::exception& e) {
        std::cout << e.what();
    }
}
