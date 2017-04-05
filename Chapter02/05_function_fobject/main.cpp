// Required for std::unary_function<> template
#include <functional>
// making a typedef for function pointer accepting int
// and returning nothing
typedef void (*func_t)(int);

// Function that accepts pointer to function and
// calls accepted function for each integer that it has
// It can not work with functional objects :(
void process_integers(func_t f);

// Functional object
class int_processor: public std::unary_function<int, void> {
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

bool g_is_triggered = false;
void set_functional_object(fobject_t& f) {
    int_processor fo( 100, 200, g_is_triggered);
    f = fo;
    // fo leaves scope and will be destroyed,
    // but 'f' will be usable even in outer scope
}

#include <vector>
#include <algorithm>
#include <boost/bind.hpp>
void foo1() {
    std::vector<int> v;
    std::for_each(v.begin(), v.end(), boost::bind(std::plus<int>(), 10, _1));

    fobject_t f(boost::bind(std::plus<int>(), 10, _1));
    std::for_each(v.begin(), v.end(), f);
}

void process_integers(const fobject_t& f) {
    static const int data[] = {1, 2, 3, 4, 5, 250};
    std::for_each(data, data + sizeof(data) / sizeof(int), f);
}
