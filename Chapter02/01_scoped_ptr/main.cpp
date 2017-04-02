#include <stdexcept>
class foo_class {
public:
    char data[100000000];

    explicit foo_class(const char* /*param*/){}
};

bool g_exit_on_first_function = true;
bool some_function1(foo_class* /*param*/) {
    return g_exit_on_first_function;
}

void some_function2(foo_class* /*param*/) {
    throw std::exception();
}

bool foo1() {
    foo_class* p = new foo_class("Some initialization data");

    const bool something_else_happened = some_function1(p);
    if (something_else_happened) {
        delete p;
        return false;
    }

    some_function2(p);
    delete p;
    return true;
}

bool foo2() {
    foo_class* p = new foo_class("Some initialization data");
    try {
        const bool something_else_happened = some_function1(p);
        if (something_else_happened) {
            delete p;
            return false;
        }

       some_function2(p);
    } catch (...) {
        delete p;
        throw;
    }

    delete p;
    return true;
}


#include <boost/scoped_ptr.hpp>

bool foo3() {
    const boost::scoped_ptr<foo_class> p(new foo_class("Some initialization data"));

    const bool something_else_happened = some_function1(p.get());
    if (something_else_happened) {
       return false;
    }

    some_function2(p.get());
    return true;
}


#include <boost/move/make_unique.hpp>

bool foo3_1() {
    const boost::movelib::unique_ptr<foo_class> p
        = boost::movelib::make_unique<foo_class>("Some initialization data");

    const bool something_else_happened = some_function1(p.get());
    if (something_else_happened) {
       return false;
    }
    some_function2(p.get());
    return true;
}

#include <assert.h>
int main() {
    try { foo2(); } catch(...){ assert(false); }
    try { foo3(); } catch(...){ assert(false); }
    try { foo3_1(); } catch(...){ assert(false); }

    g_exit_on_first_function = false;
    try { foo2(); assert(false); } catch(...){}
    try { foo3(); assert(false); } catch(...){}
    try { foo3_1(); assert(false); } catch(...){}
}

