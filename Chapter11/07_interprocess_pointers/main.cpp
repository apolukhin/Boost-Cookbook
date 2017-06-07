#include <iostream>

struct with_pointer {
    int* pointer_;
    // ...
    int value_holder_;
};


#include <boost/interprocess/offset_ptr.hpp>

struct correct_struct {
    boost::interprocess::offset_ptr<int> pointer_;
    // ...
    int value_holder_;
};


#include <boost/interprocess/managed_shared_memory.hpp>

template <class T>
void test() {
    typedef T correct_struct;
    static const int ethalon_value = 777;

    boost::interprocess::managed_shared_memory 
        segment(boost::interprocess::open_or_create, "segment", 4096);

    correct_struct* ptr =
        segment.find<correct_struct>("structure").first;

    if (ptr) {
        std::cout << "Structure found\n";
        assert(*ptr->pointer_ == ethalon_value);
        segment.destroy<correct_struct>("structure");
    } else {
        std::cout << "Creating structure\n";
        correct_struct& ref = *segment.construct<correct_struct>("structure")();
        ref.pointer_ = &ref.value_holder_;
        assert(ref.pointer_ == &ref.value_holder_);
        assert(*ref.pointer_ == ref.value_holder_);
        ref.value_holder_ = ethalon_value;
        assert(*ref.pointer_ == ethalon_value);
    }
}


#include <cassert>

int main() {
    test<correct_struct>(); // Shall be OK
    //test<with_pointer>(); // Shall fail
}
