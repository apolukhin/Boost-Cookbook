#include <vector>
#include <boost/thread/mutex.hpp>

typedef int item_t;

namespace first_attempt {

class user {
    boost::mutex        loot_mutex_;
    std::vector<item_t> loot_;
public:
    // ...

    void exchange_loot(user& u);
};

} // namespace first_attempt

#include <boost/thread/mutex.hpp>
#include <boost/thread/locks.hpp>

void first_attempt::user::exchange_loot(user& u) {
    // Terribly wrong!!! ABBA deadlocks.
    boost::lock_guard<boost::mutex> l0(loot_mutex_);
    boost::lock_guard<boost::mutex> l1(u.loot_mutex_);
    loot_.swap(u.loot_);
}



namespace second_attempt {

class user {
    boost::mutex        loot_mutex_;
    std::vector<item_t> loot_;
public:
    // ...

    void exchange_loot(user& u);
};

} // namespace second_attempt

#ifndef BOOST_NO_CXX11_VARIADIC_TEMPLATES

#include <boost/thread/lock_factories.hpp>
void second_attempt::user::exchange_loot(user& u) {
    typedef boost::unique_lock<boost::mutex> lock_t;

    std::tuple<lock_t, lock_t> l = boost::make_unique_locks(
        loot_mutex_, u.loot_mutex_
    );

    loot_.swap(u.loot_);
}


#endif // #ifndef BOOST_NO_CXX11_VARIADIC_TEMPLATES



#ifdef __cpp_lib_scoped_lock
#include <mutex>
namespace cpp17_attempt {

class user {
    std::mutex        loot_mutex_;
    std::vector<item_t> loot_;
public:
    // ...

    void exchange_loot(user& u);
};

} // namespace cpp17_attempt

void cpp17_attempt::user::exchange_loot(user& u) {
    std::scoped_lock l(loot_mutex_, u.loot_mutex_);
    loot_.swap(u.loot_);
}

#endif // __cpp_lib_scoped_lock



namespace portable_attempt {

class user {
    boost::mutex        loot_mutex_;
    std::vector<item_t> loot_;
public:
    // ...

    void exchange_loot(user& u);
};

#include <boost/thread/locks.hpp>

void user::exchange_loot(user& u) {
    typedef boost::unique_lock<boost::mutex> lock_t;

    lock_t l0(loot_mutex_, boost::defer_lock);
    lock_t l1(u.loot_mutex_, boost::defer_lock);
    boost::lock(l0, l1);

    loot_.swap(u.loot_);
}

} // namespace last_attempt



template <class UserType>
void do_test() {
    UserType u1;
    UserType u2;

    u1.exchange_loot(u2);
}


int main() {
    do_test<first_attempt::user>(); // Intentionally has ABBA deadlock!

#ifndef BOOST_NO_CXX11_VARIADIC_TEMPLATES
    do_test<second_attempt::user>();
#endif
#ifdef __cpp_lib_scoped_lock
    do_test<cpp17_attempt::user>();
#endif
    do_test<portable_attempt::user>();
}
