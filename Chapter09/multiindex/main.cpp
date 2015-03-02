#include <string>

std::size_t next_id();

struct person {
    std::size_t     id_;
    std::string     name_;
    unsigned int    height_;
    unsigned int    weight_;

    person(std::size_t id, const std::string& name, unsigned int height, unsigned int weight)
        : id_(id)
        , name_(name)
        , height_(height)
        , weight_(weight)
    {}
};

inline bool operator < (const person& p1, const person& p2) {
    return p1.name_ < p2.name_;
}

#include <iostream>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/identity.hpp>
#include <boost/multi_index/member.hpp>

template <std::size_t IndexNo, class Indexes>
void print(const Indexes& persons) {
    std::cout << IndexNo << ":\n";
    typedef typename Indexes::template nth_index<
            IndexNo
    >::type::const_iterator const_iterator_t;

    for (const_iterator_t it = persons.template get<IndexNo>().begin(),
         iend = persons.template get<IndexNo>().end();
         it != iend;
         ++it)
    {
        const person& v = *it;
        std::cout 
            << v.name_ << ", " 
            << v.id_ << ", " 
            << v.height_ << ", " 
            << v.weight_ << '\n'
        ;
    }
    
    std::cout << '\n';
}

void example_main() {
    typedef boost::multi_index::multi_index_container<
        person,
        boost::multi_index::indexed_by<
            // names are unique
            boost::multi_index::ordered_unique<
                boost::multi_index::identity<person>
            >,

            // IDs are not unique, but we do not need then ordered
            boost::multi_index::hashed_non_unique<
                boost::multi_index::member<
                    person, std::size_t, &person::id_
                >
            >,

            // Height may not be unique, but must be sorted
            boost::multi_index::ordered_non_unique<
                boost::multi_index::member<
                    person, unsigned int, &person::height_
                >
            >,

            // Weight may not be unique, but must be sorted
            boost::multi_index::ordered_non_unique<
                boost::multi_index::member<
                    person, unsigned int, &person::weight_
                >
            >
        > // closing for `boost::multi_index::indexed_by<`
    > indexes_t;

    indexes_t persons;
    
    // Inserting values
    persons.insert(person(1, "John Snow", 185, 80));
    persons.insert(person(2, "Vasya Pupkin", 165, 60));
    persons.insert(person(3, "Antony Polukhin", 183, 70));
    // Same person as "Antony Polukhin"
    persons.insert(person(3, "Anton Polukhin", 182, 70));

    print<0>(persons);
    print<1>(persons);
    print<2>(persons);
    print<3>(persons);


    assert(persons.get<1>().find(2)->name_ == "Vasya Pupkin");
    assert(
        persons.find(person(
            77, "Anton Polukhin", 0, 0
        )) != persons.end()
    );

    // Won' compile
    //assert(persons.get<0>().find("John Snow")->id_ == 1);

    typedef indexes_t::nth_index<0>::type::const_iterator const_iterator_t;
    for (const_iterator_t it = persons.get<0>().begin(),
         iend = persons.get<0>().end();
         it != iend;
         ++it)
    {
        const person& v = *it;
        // ...
        (void)v;
    }
}

// Almost the same code using tags
namespace tag {
    struct name;
    struct id;
    struct height;
    struct weight;
}

void example_2() {
    typedef boost::multi_index::multi_index_container<
        person,
        boost::multi_index::indexed_by<
            // names are unique
            boost::multi_index::ordered_unique<
                boost::multi_index::tag<tag::name>,
                boost::multi_index::member<person, std::string, &person::name_>
            >,

            // IDs are not unique, but we do not need then ordered
            boost::multi_index::hashed_non_unique<
                boost::multi_index::tag<tag::id>,
                boost::multi_index::member<person, std::size_t, &person::id_>
            >,

            // Height shall not be unique, but shall be sorted
            boost::multi_index::ordered_non_unique<
                boost::multi_index::tag<tag::height>,
                boost::multi_index::member<person, unsigned int, &person::height_>
            >,

            // Weight shall not be unique, but shall be sorted
            boost::multi_index::ordered_non_unique<
                boost::multi_index::tag<tag::weight>,
                boost::multi_index::member<person, unsigned int, &person::weight_>
            >
        > // closing for `boost::multi_index::indexed_by<`
    > indexes_t;

    indexes_t persons;
    
    // Inserting values
    persons.insert(person(1, "John Snow", 185, 80));
    persons.insert(person(2, "Vasya Pupkin", 165, 60));
    persons.insert(person(3, "Antony Polukhin", 183, 70));
    // Same person as "Antony Polukhin"
    persons.insert(person(3, "Anton Polukhin", 182, 70));
    
    // Now it compiles
    assert(persons.get<tag::name>().find("John Snow")->id_ == 1);
    
    assert(persons.get<tag::id>().find(2)->name_ == "Vasya Pupkin");

    // Same as `persons.get<0>().find("Anton Polukhin")`
    assert(persons.find("Anton Polukhin")->id_ == 3);
}

int main() {
    example_main();
    example_2();
}




