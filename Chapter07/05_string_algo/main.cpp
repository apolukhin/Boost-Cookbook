#include <iostream>
#include <string>
const std::string str = "Hello, hello, dear Reader.";

#include <boost/algorithm/string/erase.hpp>
void erasing_examples() {
    namespace ba = boost::algorithm;
    using std::cout;

    cout<<"\n erase_all_copy  :" << ba::erase_all_copy(str, ",");
    cout<<"\n erase_first_copy:" << ba::erase_first_copy(str, ",");
    cout<<"\n erase_last_copy :" << ba::erase_last_copy(str, ",");
    cout<<"\n ierase_all_copy :" << ba::ierase_all_copy(str, "hello");
    cout<<"\n ierase_nth_copy :" << ba::ierase_nth_copy(str, ",", 1);
}

#include <boost/algorithm/string/replace.hpp>
void replacing_examples() {
    namespace ba = boost::algorithm;
    using std::cout;

    cout << "\n replace_all_copy  :" 
        << ba::replace_all_copy(str, ",", "!");

    cout << "\n replace_first_copy  :"
        << ba::replace_first_copy(str, ",", "!");

    cout << "\n replace_head_copy  :"
        << ba::replace_head_copy(str, 6, "Whaaaaaaa!");
}

#include <boost/algorithm/string/erase.hpp>
void erasing_examples_locale() {
    namespace ba = boost::algorithm;
    
    const std::locale loc = std::locale::classic();

    const std::string r1
        = ba::ierase_all_copy(str, "hello", loc);

    const std::string r2
        = ba::ierase_nth_copy(str, ",", 1, loc);
    // ...
    assert(r1 == ba::ierase_all_copy(str, "hello"));
    assert(r2 == ba::ierase_nth_copy(str, ",", 1));
}

int main() {
    erasing_examples();
    replacing_examples();
    erasing_examples_locale();
}

