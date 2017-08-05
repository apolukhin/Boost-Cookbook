#include <boost/function.hpp>
typedef boost::function<void(int)> fobject_t;

// Now this function may accept functional objects
void process_integers(const fobject_t& f);



#include <cassert>
#include <deque>
//#include <your_project/process_integers.h>

void sample() {
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



int main() {
    sample();

    std::deque<int> v = {10, 20, 30, 40, 50};

    std::for_each(v.begin(), v.end(), [](int& v) { v += 10; });

    const boost::function<void(int&)> f0(
        [](int& v) { v += 10; }
    );
    std::for_each(v.begin(), v.end(), f0);

    const auto f1 = [](int& v) { v += 10; };
    std::for_each(v.begin(), v.end(), f1);
}

void process_integers(const fobject_t& f) {
    static const int data[] = {1, 2, 3, 4, 5, 200};
    // We'll be using only 6 elements in this example
    std::for_each(data, data + 6, f);
}
