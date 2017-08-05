#include <set>
#include <algorithm>
#include <cassert>

template <class T>
struct ptr_cmp {
    template <class T1>
    bool operator()(const T1& v1, const T1& v2) const {
        return operator ()(*v1, *v2);
    }

    bool operator()(const T& v1, const T& v2) const {
        return std::less<T>()(v1, v2);
    }
};

void example1() {
    std::set<int*, ptr_cmp<int> > s;
    s.insert(new int(1));
    s.insert(new int(0));

    // ...
    assert(**s.begin() == 0);
    // ...

    // Oops! Any exception in the above code leads to
    // memory leak.

    // Deallocating resources.
    std::for_each(s.begin(), s.end(), [](int* p) { delete p; });
}



#include <memory>
#include <set>

void example2_cpp11() {
    typedef std::unique_ptr<int> int_uptr_t;
    std::set<int_uptr_t, ptr_cmp<int> > s;
    s.insert(int_uptr_t(new int(1)));
    s.insert(int_uptr_t(new int(0)));

    // ...
    assert(**s.begin() == 0);
    // ...

    // Resources will be deallocated by unique_ptr<>.
}



#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

void example3() {
    typedef boost::shared_ptr<int> int_sptr_t;
    std::set<int_sptr_t, ptr_cmp<int> > s;
    s.insert(boost::make_shared<int>(1));
    s.insert(boost::make_shared<int>(0));

    // ...
    assert(**s.begin() == 0);
    // ...

    // Resources will be deallocated by shared_ptr<>.
}



#include <boost/ptr_container/ptr_set.hpp>

void correct_impl() {
    boost::ptr_set<int> s;
    s.insert(new int(1));
    s.insert(new int(0));

    // ...
    assert(*s.begin() == 0);
    // ...

    // Resources will be deallocated by container itself.
}



#include <boost/ptr_container/clone_allocator.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <cassert>

void theres_more_example() {
    // Creating vector of 10 elements with values 100
    boost::ptr_vector<int> v;
    int value = 100;
    v.resize(10, &value); // Beware! No ownership of pointer!

    assert(v.size() == 10);
    assert(v.back() == 100);
}



#include <boost/container/set.hpp>
#include <boost/move/make_unique.hpp>
#include <cassert>

void example2_cpp03() {
    typedef boost::movelib::unique_ptr<int> int_uptr_t;
    boost::container::set<int_uptr_t, ptr_cmp<int> > s;
    s.insert(boost::movelib::make_unique<int>(1));
    s.insert(boost::movelib::make_unique<int>(0));
    // ...
    assert(**s.begin() == 0);
}



int main() {
    example1();
    example2_cpp11();
    example3();
    correct_impl();
    theres_more_example();
    example2_cpp03();
}
