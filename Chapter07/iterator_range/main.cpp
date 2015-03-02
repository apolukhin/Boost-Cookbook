#include <iostream>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <algorithm>

int main() {
    const char str[] 
        = "This is a long long character array."
          "Please split this character array to sentences!"
          "Do you know, that sentences are separated using period, "
          "exclamation mark and question mark? :-)"
          ; 
    
    typedef boost::split_iterator<const char*> split_iter_t; 
    split_iter_t sentences = boost::make_split_iterator(str, 
        boost::algorithm::token_finder(boost::is_any_of("?!."))
    );    
    
    
    for (unsigned int i = 1; !sentences.eof(); ++sentences, ++i) {
        boost::iterator_range<const char*> range = *sentences;
        std::cout << "Sentence #" << i << " : \t" << range << '\n';
        std::cout << "Sentence has " << range.size() << " characters.\n";
        std::cout 
            << "Sentence has " 
            << std::count(range.begin(), range.end(), ' ') 
            << " whitespaces.\n\n";
    } // end of for(...) loop
} // end of main()
