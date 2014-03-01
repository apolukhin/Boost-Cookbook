#include <map>
#include <boost/thread/mutex.hpp>
#include <boost/thread/locks.hpp>

struct user_info {
    std::string address;
    unsigned short age;

    // Other parameters
    // ...
};

namespace first_example {

class users_online {
    typedef boost::mutex                mutex_t;
    mutable mutex_t                     users_mutex_;
    std::map<std::string, user_info>    users_;

public:
    bool is_online(const std::string& username) const {
        boost::lock_guard<mutex_t> lock(users_mutex_);
        return users_.find(username) != users_.end();
    }

    unsigned short get_age(const std::string& username) const {
        boost::lock_guard<mutex_t> lock(users_mutex_);
        return users_.at(username).age;
    }

    void set_online(const std::string& username, const user_info& data) {
        boost::lock_guard<mutex_t> lock(users_mutex_);
        users_.insert(std::make_pair(username, data));
    }

    // Other methods
    // ...
};

}

#include <boost/thread/shared_mutex.hpp>

namespace shared_lock_example {

class users_online {
    typedef boost::shared_mutex         mutex_t;
    mutable mutex_t                     users_mutex_;
    std::map<std::string, user_info>    users_;

public:
    bool is_online(const std::string& username) const {
        boost::shared_lock<mutex_t> lock(users_mutex_);
        return users_.find(username) != users_.end();
    }

    unsigned short get_age(const std::string& username) const {
        boost::shared_lock<mutex_t> lock(users_mutex_);
        return users_.at(username).age;
    }

    void set_online(const std::string& username, const user_info& data) {
        boost::lock_guard<mutex_t> lock(users_mutex_);
        users_.insert(std::make_pair(username, data));
    }

    // Other methods
    // ...
};

}

#include <boost/thread/thread.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/bind.hpp>
#include <boost/ref.hpp>

const std::size_t users_count = 1000000;

template <class T>
void log_in(T& u, std::size_t count) {
    for (std::size_t i = 0; i < count; ++i) {
        u.set_online(boost::lexical_cast<std::string>(i), user_info());
    }
}

template <class T>
void thread_get_age(T& u) {
    for (std::size_t i = 0; i < users_count; ++i) {
        u.get_age(boost::lexical_cast<std::string>(i));
    }
}

template <class T>
void thread_is_online(T& u) {
    for (std::size_t i = 0; i < users_count; ++i) {
        assert(u.is_online(boost::lexical_cast<std::string>(i)));
    }
}

int main() {
    //using namespace first_example;
    using namespace shared_lock_example;
    users_online users;

    log_in(users, users_count);

    boost::thread t1(boost::bind(&thread_get_age<users_online>, boost::ref(users)));
    boost::thread t2(boost::bind(&thread_get_age<users_online>, boost::ref(users)));
    boost::thread t3(boost::bind(&thread_is_online<users_online>, boost::ref(users)));
    boost::thread t4(boost::bind(&thread_is_online<users_online>, boost::ref(users)));

    boost::thread t5(boost::bind(&log_in<users_online>, boost::ref(users), 5));
    boost::thread t6(boost::bind(&log_in<users_online>, boost::ref(users), 25));

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    t5.join();
    t6.join();
}
