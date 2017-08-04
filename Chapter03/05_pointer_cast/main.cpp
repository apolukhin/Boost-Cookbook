struct base {
    virtual void some_methods() = 0;
    virtual ~base();
};

struct derived: public base {
    void some_methods() /*override*/;
    virtual void derived_method() const;

    ~derived() /*override*/;
};


#include <boost/shared_ptr.hpp>
boost::shared_ptr<const base> construct_derived();
void im_accepting_derived(boost::shared_ptr<const derived> p);

/*

void trying_hard_to_pass_derived() {
    boost::shared_ptr<const base> d = construct_derived();

    // Oops! Compile time error:
    // ‘const struct base’ has no member named ‘derived_method’.
    d->derived_method();

    // Oops! Compile time error:
    // could not convert ‘d’ to ‘boost::shared_ptr<const derived>’.
    im_accepting_derived(d);
}

*/

#include <stdexcept>

void trying_hard_to_pass_derived2() {
    boost::shared_ptr<const derived> d
        = boost::dynamic_pointer_cast<const derived>(
            construct_derived()
        );

    if (!d) {
        throw std::runtime_error(
            "Failed to dynamic cast"
        );
    }

    d->derived_method();
    im_accepting_derived(d);
}

int main() {
    trying_hard_to_pass_derived2();
}



// Implementation details:

#include <cassert>
#include <boost/make_shared.hpp>

bool g_derived_was_called = false;
base::~base() {
    assert(g_derived_was_called);
}

void derived::derived_method() const {
    g_derived_was_called = true;
}

void derived::some_methods() {}

derived::~derived() {}

boost::shared_ptr<const base> construct_derived() {
    return boost::make_shared<derived>();
}

void im_accepting_derived(boost::shared_ptr<const derived> p) {
    assert(p);
}
