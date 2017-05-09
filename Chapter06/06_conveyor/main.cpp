#include <vector>
struct data_packet { unsigned int value; };
struct decoded_data { unsigned int value; };
struct compressed_data { unsigned int value; };

#include <boost/atomic.hpp>
typedef boost::atomic<unsigned int> atomic_t;

class subsystem1 {
    atomic_t i_;
public:
    subsystem1() :
        i_(0)
    {}

    data_packet get_data() {
        data_packet ret = { ++ i_ };
        return ret;
    }

    static const unsigned int max_runs = 10000; // 10 000 runs

    bool is_stopped() const {
        return i_ == max_runs; // 10 000 runs
    }
};

#include <cassert>
class subsystem2 {
    atomic_t i_;
public:
    subsystem2() :
        i_(0)
    {}

    void send_data(const compressed_data& data) {
        ++ i_;
        assert(data.value == i_);
    }

    unsigned int send_packets_count() const {
        return i_;
    }
};

decoded_data decode_data(const data_packet& packet) {
    static unsigned int i = 0;
    ++ i;
    decoded_data ret = { packet.value };
    assert(i == packet.value);
    return ret;
}

compressed_data compress_data(const decoded_data& packet) {
    static unsigned int i = 0;
    ++ i;
    compressed_data ret = { packet.value };
    assert(i == packet.value);
    return ret;
}


// class work_queue from chapter 5
#include <deque>
#include <boost/function.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/locks.hpp>
#include <boost/thread/condition_variable.hpp>

class work_queue {
public:
    typedef boost::function<void()> task_type;

private:
    std::deque<task_type>   tasks_;
    boost::mutex            mutex_;
    boost::condition_variable cond_;
    bool                    is_stopped_;

public:
    work_queue()
        : is_stopped_(false)
    {}

    void stop() {
        boost::lock_guard<boost::mutex> lock(mutex_);
        is_stopped_ = true;
        cond_.notify_all();
    }
    
    void push_task(const task_type& task) {
        boost::unique_lock<boost::mutex> lock(mutex_);
        if (is_stopped_) {
            return;
        }
        tasks_.push_back(task);
        lock.unlock();
        cond_.notify_one();
    }

    task_type pop_task() {
        boost::unique_lock<boost::mutex> lock(mutex_);
        while (tasks_.empty()) {
            if (is_stopped_) {
                return task_type();
            }
            cond_.wait(lock);
        }

        task_type ret = tasks_.front();
        tasks_.pop_front();

        return ret;
    }
};

//#define RUN_BAD_EXAMPLE
#ifdef RUN_BAD_EXAMPLE
// global variables
tasks_queue queue; 
subsystem1 subs1;
subsystem2 subs2;

tasks_queue& operator<< (tasks_queue&, data_packet& data) {
    decoded_data d_decoded = decode_data(data);
    compressed_data c_data = compress_data(d_decoded);
    subs2.send_data(c_data);
}

void start_data_accepting() {
    while (!subs1.is_stopped()) {
        queue << subs1.get_data();
    }
}

#include <boost/thread/thread.hpp>
int main() {
    // Getting data packets from first device
    // and putting them to queue
    boost::thread t(&start_data_accepting);

    // Which data packet will be processed first in
    // multi-threaded environment?
    // packet #2 may be processed before packet #1,
    // no guarantee that packets will be processed in
    // order of their apperance
    queue.run_multiple();
    t.join();
}

#else

// global variables
work_queue decoding_queue, compressing_queue, sending_queue;
subsystem1 subs1;
subsystem2 subs2;

#include <boost/bind.hpp>
void do_decode(const data_packet& packet);
void start_data_accepting() {
    while (!subs1.is_stopped()) {
        decoding_queue.push_task(boost::bind(
            &do_decode, subs1.get_data()
        ));
    }
}

void do_compress(const decoded_data& packet);
void do_decode(const data_packet& packet) {
    compressing_queue.push_task(boost::bind(
        &do_compress, decode_data(packet)
    ));
}


void do_compress(const decoded_data& packet) {
    sending_queue.push_task(boost::bind(
        &subsystem2::send_data,
        boost::ref(subs2),
        compress_data(packet)
    ));
}

void run_while_not_stopped(work_queue& queue) {
    work_queue::task_type task;
    while (task = queue.pop_task()) {
        task();
    }
}

#include <boost/thread/thread.hpp>
int main() {
    // Getting data packets from first device and putting them to queue
    boost::thread t_data_accepting(&start_data_accepting);
    boost::thread t_data_decoding(boost::bind(
        &run_while_not_stopped, boost::ref(decoding_queue)
    ));
    boost::thread t_data_compressing(boost::bind(
        &run_while_not_stopped, boost::ref(compressing_queue)
    ));
    boost::thread t_data_sending(boost::bind(
        &run_while_not_stopped, boost::ref(sending_queue)
    ));

    t_data_accepting.join();

    decoding_queue.stop();
    t_data_decoding.join();

    compressing_queue.stop();
    t_data_compressing.join();

    sending_queue.stop();
    t_data_sending.join();

    assert(subs2.send_packets_count() == subsystem1::max_runs);
}

#endif
