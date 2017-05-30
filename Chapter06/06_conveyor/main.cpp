struct data_packet { unsigned int value; };
struct decoded_data { unsigned int value; };
struct compressed_data { unsigned int value; };

#include <boost/atomic.hpp>
#include <boost/noncopyable.hpp>
typedef boost::atomic<unsigned int> atomic_t;

class subsystem1: boost::noncopyable {
    atomic_t i_;
public:
    subsystem1();

    data_packet get_data();

    static const unsigned int max_runs = 10000;

    bool is_stopped() const;
};

class subsystem2: boost::noncopyable {
    atomic_t i_;
public:
    subsystem2();

    void send_data(const compressed_data& data);
    unsigned int send_packets_count() const;
};


#include <boost/thread/thread.hpp>

subsystem1 subs1;
subsystem2 subs2;

decoded_data decode_data(const data_packet& packet);
compressed_data compress_data(const decoded_data& packet);

void process_data() {
    while (!subs1.is_stopped()) {
        data_packet data = subs1.get_data();
        decoded_data d_decoded = decode_data(data);
        compressed_data c_data = compress_data(d_decoded);
        subs2.send_data(c_data);
    }
}

void run_in_multiple_threads() {
    boost::thread t(&process_data);
    process_data();

    t.join();
}

//////////////

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
    std::deque<task_type>       tasks_;
    boost::mutex                mutex_;
    boost::condition_variable   cond_;
    bool                        is_stopped_;

public:
    work_queue()
        : is_stopped_(false)
    {}

    void run();
    void stop();
    
    // Same as in Chapter 5, but with
    // rvalue references support.
    void push_task(task_type&& task);
};

//////////////

// global variables
work_queue decoding_queue, compressing_queue, sending_queue;

void start_data_accepting();
void do_decode(const data_packet& packet);
void do_compress(const decoded_data& packet);

void start_data_accepting() {
    while (!subs1.is_stopped()) {
        data_packet packet = subs1.get_data();

        decoding_queue.push_task(
            [packet]() {
                do_decode(packet);
            }
        );
    }
}

void do_decode(const data_packet& packet) {
    decoded_data d_decoded = decode_data(packet);

    compressing_queue.push_task(
        [d_decoded]() {
            do_compress(d_decoded);
        }
    );
}

void do_compress(const decoded_data& packet) {
    compressed_data c_data = compress_data(packet);
        
    sending_queue.push_task(
        [c_data]() {
            subs2.send_data(c_data);
        }
    );
}


#include <boost/thread/thread.hpp>
int main() {
    boost::thread t_data_decoding(
        []() { decoding_queue.run(); }
    );
    boost::thread t_data_compressing(
        []() { compressing_queue.run(); }
    );
    boost::thread t_data_sending(
        []() { sending_queue.run(); }
    );

    start_data_accepting();

    decoding_queue.stop();
    t_data_decoding.join();

    compressing_queue.stop();
    t_data_compressing.join();

    sending_queue.stop();
    t_data_sending.join();

    assert(subs2.send_packets_count() == subsystem1::max_runs);



    run_in_multiple_threads(); // Making coverage tools happy.
}


void work_queue::stop() {
    boost::lock_guard<boost::mutex> lock(mutex_);
    is_stopped_ = true;
    cond_.notify_all();
}

void work_queue::run() {
    while (1) {
        boost::unique_lock<boost::mutex> lock(mutex_);
        while (tasks_.empty()) {
            if (is_stopped_) {
                return;
            }
            cond_.wait(lock);
        }

        task_type t = std::move(tasks_.front());
        tasks_.pop_front();
        lock.unlock();

        t();
    }
}



void work_queue::push_task(task_type&& task) {
    boost::unique_lock<boost::mutex> lock(mutex_);
    if (is_stopped_) {
        return;
    }
    tasks_.push_back(std::move(task));
    lock.unlock();
    cond_.notify_one();
}

subsystem1::subsystem1()
    : i_(0)
{}

data_packet subsystem1::get_data() {
    data_packet ret = { ++ i_ };
    return ret;
}

  
bool subsystem1::is_stopped() const {
    return i_ == max_runs; // 10 000 runs
}

#include <cassert>

subsystem2::subsystem2()
    : i_(0)
{}

void subsystem2::send_data(const compressed_data& data) {
    ++ i_;
    assert(data.value == i_);
}

unsigned int subsystem2::send_packets_count() const {
    return i_;
}

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

