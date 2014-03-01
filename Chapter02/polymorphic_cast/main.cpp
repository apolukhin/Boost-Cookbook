#include <boost/cast.hpp>

struct object {
    virtual ~object() {}
};

struct banana: public object {
    void eat() const {}
    virtual ~banana(){}
};

struct pidgin: public object {
    void fly() const {}
    virtual ~pidgin(){}
};

object* try_produce_banana();

void try_eat_banana_impl1() {
    const object* obj = try_produce_banana();
    if (!obj) {
        throw std::bad_cast();
    }

    dynamic_cast<const banana&>(*obj).eat();
}

void try_eat_banana_impl2() {
    const object* obj = try_produce_banana();
    boost::polymorphic_cast<const banana*>(obj)->eat();
}



object* try_produce_banana() {
    static pidgin pidg;
    static banana banan;
    static int i = 0;
    ++ i;
    if (i == 3 || i == 6) {
        return 0;
    } else if (i == 2 || i == 5) {
        return &pidg;
    }
    return &banan;
}

#include <iostream>
using namespace std;

int main()
{

    try_eat_banana_impl1();

    try {
        try_eat_banana_impl1();
        assert(false);
    } catch(...){}

    try {
        try_eat_banana_impl1();
        assert(false);
    } catch(...){}

    try_eat_banana_impl2();
    try {
        try_eat_banana_impl2();
        assert(false);
    } catch(...){}

    try {
        try_eat_banana_impl2();
        assert(false);
    } catch(...){}
    return 0;
}

