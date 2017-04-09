// making a typedef for function pointer accepting int
// and returning nothing
typedef void (*func_t)(int);

// Function that accepts pointer to function and
// calls accepted function for each integer that it has.
// It cannot work with functional objects :(
void process_integers(func_t f);

// Functional object
class int_processor {
   const int min_;
   const int max_;
   bool& triggered_;

public:
    int_processor(int min, int max, bool& triggered)
        : min_(min)
        , max_(max)
        , triggered_(triggered)
    {}

    void operator()(int i) const {
        if (i < min_ || i > max_) {
            triggered_ = true;
        }
    }
};

#include <boost/function.hpp>
typedef boost::function<void(int)> fobject_t;

// Now this function may accept functional objects
void process_integers(const fobject_t& f);

int main() {
    bool is_triggered = false;
    int_processor fo(0, 200, is_triggered);
    process_integers(fo);
    assert(is_triggered);
}

bool g_is_triggered = false;
void set_functional_object(fobject_t& f) {
    // Local variable
    int_processor fo( 100, 200, g_is_triggered);

    f = fo;
    // now 'f' holds a copy of 'fo'

    // 'fo' leavs scope and will be destroyed,
    // but it's OK to use 'f' in outer scope.
}


void foo(const fobject_t& f) {
    // boost::function is convertible to bool
    if (f) {
        // we have value in 'f'
        // ...
    } else {
        // 'f' is empty
        // ...
    }
}

void process_integers(const fobject_t& f) {
    static const int data[] = {1, 2, 3, 4, 5, 250};
    std::for_each(data, data + sizeof(data) / sizeof(int), f);
}


// Making sure that `set_functional_object` works as expected
struct more_tests_runner {
    more_tests_runner() {
        fobject_t out;
        assert(!out);
        set_functional_object(out);
        assert(out);

        foo(out);
    }
};
more_tests_runner more_tests;
