// Contains boost::bind and placeholders.
#include <boost/bind.hpp>

// Utility stuff required by samples.
#include <boost/array.hpp>
#include <algorithm>
#include <functional>
#include <string>
#include <cassert>



void sample1() {
    const boost::array<int, 12> v = {{
        1, 2, 3, 4, 5, 6, 7, 100, 99, 98, 97, 96
    }};

    const std::size_t count0 = std::count_if(v.begin(), v.end(),
        [](int x) { return 5 < x; }
    );
    const std::size_t count1 = std::count_if(v.begin(), v.end(),
        boost::bind(std::less<int>(), 5, _1)
    );
    assert(count0 == count1);
}



void sample2() {
    const boost::array<std::string, 3> v = {{
        "We ", "are", " the champions!"
    }};

    const std::size_t count0 = std::count_if(v.begin(), v.end(),
        [](const std::string& s) { return s.empty(); }
    );
    const std::size_t count1 = std::count_if(v.begin(), v.end(),
        boost::bind(&std::string::empty, _1)
    );
    assert(count0 == count1);
}



void sample3() {
    const boost::array<std::string, 3> v = {{
        "We ", "are", " the champions!"
    }};

    const std::size_t count0 = std::count_if(v.begin(), v.end(), 
        [](const std::string& s) {  return s.size() < 5; }
    ); 
    const std::size_t count1 = std::count_if(v.begin(), v.end(), 
        boost::bind(
            std::less<std::size_t>(),
            boost::bind(&std::string::size, _1),
            5
        )
    ); 
    assert(count0 == count1);  
}



void sample4() {
    const boost::array<std::string, 3> v = {{
        "We ", "are", " the champions!"
    }}; 
    std::string s(
        "Expensive copy constructor is called when binding"
    ); 

    const std::size_t count0 = std::count_if(v.begin(), v.end(),
        [&s](const std::string& x) {  return x < s; }
    ); 
    const std::size_t count1 = std::count_if(v.begin(), v.end(), 
        boost::bind(std::less<std::string>(), _1, s)
    ); 
    assert(count0 == count1);
}



#include <boost/ref.hpp>

void sample5() {
    const boost::array<std::string, 3> v = {{
        "We ", "are", " the champions!"
    }}; 
    std::string s(
        "Expensive copy constructor is NOT called when binding"
    ); 

    const std::size_t count1 = std::count_if(v.begin(), v.end(), 
        boost::bind(std::less<std::string>(), _1, boost::cref(s))
    ); 
    // ...



    const std::size_t count0 = std::count_if(v.begin(), v.end(), [&s](const std::string& x) {
        return x < s;
    });
    assert(count0 == count1);
}



void sample6() {
    const auto twice = boost::bind(std::plus<int>(), _1, _1);
    assert(twice(2) == 4);

    const auto minus_from_second = boost::bind(std::minus<int>(), _2, _1);
    assert(minus_from_second(2, 4) == 2);

    const auto sum_second_and_third = boost::bind(
        std::plus<int>(), _2, _3
    );
    assert(sum_second_and_third(10, 20, 30) == 50);
}


int main () {
    sample1();
    sample2();
    sample3();
    sample4();
    sample5();
    sample6();
}



