void example1();
void example2();

#include <iostream>
#include <boost/bimap.hpp>
#include <boost/bimap/multiset_of.hpp>

int main() {
    typedef boost::bimap<
        std::string,
        boost::bimaps::multiset_of<std::size_t>
    > name_id_type;

    name_id_type name_id;
    
    // Inserting keys <-> values
    name_id.insert(name_id_type::value_type(
        "John Snow", 1
    ));

    name_id.insert(name_id_type::value_type(
        "Vasya Pupkin", 2
    ));
    
    name_id.insert(name_id_type::value_type(
        "Antony Polukhin", 3
    ));

    // Same person as "Antony Polukhin"
    name_id.insert(name_id_type::value_type(
        "Anton Polukhin", 3
    ));


    std::cout << "Left:\n";
 
    typedef name_id_type::left_const_iterator left_const_iterator;
    const left_const_iterator lend = name_id.left.end();

    for (left_const_iterator it = name_id.left.begin();
         it!= lend;
         ++it)
    {
        std::cout << it->first << " <=> " << it->second << '\n';
    }

    std::cout << "\nRight:\n";

    typedef name_id_type::right_const_iterator right_const_iterator;
    const right_const_iterator rend = name_id.right.end();

    for (right_const_iterator it = name_id.right.begin();
         it!= rend;
         ++it)
    {
        std::cout << it->first << " <=> " << it->second << '\n';
    }

    assert(name_id.left.find("John Snow")->second == 1);
    assert(name_id.right.find(2)->second == "Vasya Pupkin");
    assert(
        name_id.find(name_id_type::value_type(
            "Anton Polukhin", 3
        )) != name_id.end()
    );
    
    example1();
    example2();
} /* end of main() */

#include <boost/bimap/set_of.hpp>
typedef boost::bimap<
    boost::bimaps::set_of<std::string>, 
    boost::bimaps::multiset_of<std::size_t> 
> name_id_type;

#include <map>
void example1() {
    name_id_type name_id;

    std::map<std::string, std::size_t> key1;      // == name_id.left
    std::multimap<std::size_t, std::string> key2; // == name_id.right
}

#include <boost/bimap/unordered_set_of.hpp>
#include <boost/bimap/unordered_multiset_of.hpp>

typedef boost::bimap<
    boost::bimaps::unordered_set_of<std::string>, 
    boost::bimaps::unordered_multiset_of<std::size_t> 
> hash_name_id_type;

void example2() {
    hash_name_id_type name_id;
}
