#include <string>
std::string str1 = "Thanks for reading me!";
std::string str2 = "Thanks for reading ME!";

#include <boost/algorithm/string/predicate.hpp>

const bool solution_1 = (
    boost::iequals(str1, str2)
);


#include <boost/algorithm/string/compare.hpp>
#include <algorithm>

const bool solution_2 = (
    str1.size() == str2.size() && std::equal(
        str1.begin(),
        str1.end(),
        str2.begin(),
        boost::is_iequal()
    )
);

#include <boost/algorithm/string/case_conv.hpp>

void solution_3() {
    std::string str1_low = boost::to_lower_copy(str1);
    std::string str2_low = boost::to_lower_copy(str2);
    assert(str1_low == str2_low);
}

#include <boost/algorithm/string/case_conv.hpp>

void solution_4() {
    std::string str1_up = boost::to_upper_copy(str1);
    std::string str2_up = boost::to_upper_copy(str2);
    assert(str1_up == str2_up);
}

#include <boost/algorithm/string/case_conv.hpp>

void solution_5() {
    boost::to_lower(str1);
    boost::to_lower(str2);
    assert(str1 == str2);
}

int main() {
    assert(solution_1);
    assert(solution_2);
    solution_3();
    solution_4();
    solution_5();

    // On some platforms std::locale::classic() works
    // faster than std::locale().
    boost::iequals(str1, str2, std::locale::classic());
}
