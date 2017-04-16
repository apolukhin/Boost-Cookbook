#include <boost/cast.hpp>

struct object {
    virtual ~object() {}
};

struct banana: public object {
    void eat() const {}
    virtual ~banana(){}
};

struct penguin: public object {
    bool try_to_fly() const {
        return false; // penguins do not fly
    }
    virtual ~penguin(){}
};

object* try_produce_banana();

void try_eat_banana_impl1() {
    const object* obj = try_produce_banana();
    if (!obj) {
        throw std::bad_cast();
    }

    dynamic_cast<const banana&>(*obj).eat();
}

#include <boost/cast.hpp>
void try_eat_banana_impl2() {
    const object* obj = try_produce_banana();
    boost::polymorphic_cast<const banana*>(obj)->eat();
}



object* try_produce_banana() {
    static penguin peng;
    static banana banan;
    static int i = 0;
    ++ i;
    if (i == 3 || i == 6) {
        return 0;
    } else if (i == 2 || i == 5) {
        return &peng;
    }
    return &banan;
}

#include <iostream>
using namespace std;

int main() {
    try_eat_banana_impl1();
    try { try_eat_banana_impl1(); assert(false); } catch(...){}
    try { try_eat_banana_impl1(); assert(false); } catch(...){}

    try_eat_banana_impl2();
    try { try_eat_banana_impl2(); assert(false); } catch(...){}
    try { try_eat_banana_impl2(); assert(false); } catch(...){}
}

