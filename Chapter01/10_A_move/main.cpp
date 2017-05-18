#include <memory>
#include <string>
#include <vector>
#include <assert.h>

#include <boost/move/move.hpp>


namespace other {
    class characteristics{};
}

struct person_info {
    std::string name_;
    std::string second_name_;
    other::characteristics characteristic_;

    // Fields declared here
    // ...
private:
    BOOST_COPYABLE_AND_MOVABLE(person_info)
public:
    // For the simplicity of example we will assume that
    // person_info default constructor and swap are very
    // fast/cheap to call
    person_info() {}

    person_info(const person_info& p)
        : name_(p.name_)
        , second_name_(p.second_name_)
        , characteristic_(p.characteristic_)
    {}

    person_info(BOOST_RV_REF(person_info) person) {
        swap(person);
    }

    person_info& operator=(BOOST_COPY_ASSIGN_REF(person_info) person) {
        person_info tmp(person);
        swap(tmp);
        return *this;
    }

    person_info& operator=(BOOST_RV_REF(person_info) person) {
        person_info tmp(boost::move(person));
        swap(tmp);
        return *this;
    }

    void swap(person_info& rhs);
};


#include <boost/swap.hpp>

void person_info::swap(person_info& rhs) {
    name_.swap(rhs.name_);
    second_name_.swap(rhs.second_name_);
    boost::swap(characteristic_, rhs.characteristic_);
}



int main() {

    person_info vasya;
    vasya.name_ = "Vasya";
    vasya.second_name_ = "Snow";

    person_info new_vasya(boost::move(vasya));
    assert(new_vasya.name_ == "Vasya");
    assert(new_vasya.second_name_ == "Snow");
    assert(vasya.name_.empty());
    assert(vasya.second_name_.empty());

    vasya = boost::move(new_vasya);
    assert(vasya.name_ == "Vasya");
    assert(vasya.second_name_ == "Snow");
    assert(new_vasya.name_.empty());
    assert(new_vasya.second_name_.empty());

    new_vasya = vasya;
    assert(vasya.name_ == "Vasya");
    assert(vasya.second_name_ == "Snow");
    assert(new_vasya.name_ == "Vasya");
    assert(new_vasya.second_name_ == "Snow");
}
