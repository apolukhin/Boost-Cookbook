#include <boost/function.hpp>
typedef boost::function<void(int)> fobject_t;

// Now this function may accept functional objects
void process_integers(const fobject_t& f);

#include <assert.h>
#include <deque>
int main() {
    // lambda function with no parameters that does nothing
    process_integers([](int /*i*/){});

    // lambda function that stores a reference
    std::deque<int> ints;
    process_integers([&ints](int i){
        ints.push_back(i);
    });

    // lambda function that modifies its content
    std::size_t match_count = 0;
    process_integers([ints, &match_count](int i) mutable {
        if (ints.front() == i) {
           ++ match_count;
        }
        ints.pop_front();
    });

    assert(match_count == 6);
}

void process_integers(const fobject_t& f) {
    static const int data[] = {1, 2, 3, 4, 5, 200, 0};
    // We'll be using only 6 elements in this example
    std::for_each(data, data + 6, f);
}
