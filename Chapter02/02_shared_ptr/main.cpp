class foo_class {
public:
    char data[10000000];

    explicit foo_class(const char* /*param*/){}
};

foo_class* get_data();


#include <boost/thread.hpp>
#include <boost/bind.hpp>

void process1(const foo_class* p);
void process2(const foo_class* p);
void process3(const foo_class* p);

void foo1() {
    while (foo_class* p = get_data()) // C way
    {
        // There will be too many threads soon, see
        // recipe 'Parallel execution of different tasks'
        // for a good way to avoid uncontrolled growth of threads
        boost::thread(boost::bind(&process1, p))
            .detach();
        boost::thread(boost::bind(&process2, p))
            .detach();
        boost::thread(boost::bind(&process3, p))
            .detach();


        // delete p; Oops!!!!
    }
}


#include <boost/shared_ptr.hpp>

void process_sp1(const boost::shared_ptr<foo_class>& p);
void process_sp2(const boost::shared_ptr<foo_class>& p);
void process_sp3(const boost::shared_ptr<foo_class>& p);

void foo2() {
    typedef boost::shared_ptr<foo_class> ptr_t;
    ptr_t p;
    while (p = ptr_t(get_data())) // C way
    {
        boost::thread(boost::bind(&process_sp1, p))
            .detach();
        boost::thread(boost::bind(&process_sp2, p))
            .detach();
        boost::thread(boost::bind(&process_sp3, p))
            .detach();

        // no need to anything
    }
}

#include <string>
#include <boost/smart_ptr/make_shared.hpp>

void process_str1(boost::shared_ptr<std::string> p);
void process_str2(const boost::shared_ptr<std::string>& p);

void foo3() {
    boost::shared_ptr<std::string> ps = boost::make_shared<std::string>(
        "Guess why make_shared<std::string> "
        "is faster than shared_ptr<std::string> "
        "ps(new std::string('this string'))"
    );
    boost::thread(boost::bind(&process_str1, ps))
            .detach();
    boost::thread(boost::bind(&process_str2, ps))
            .detach();
}

void process_cstr1(boost::shared_ptr<const std::string> p);
void process_cstr2(const boost::shared_ptr<const std::string>& p);

void foo3_const() {
    boost::shared_ptr<const std::string> ps
        = boost::make_shared<const std::string>(
            "Some immutable string"
        );

    boost::thread(boost::bind(&process_cstr1, ps))
            .detach();
    boost::thread(boost::bind(&process_cstr2, ps))
            .detach();

    // *ps = "qwe"; // Compile time error, string is const!
}

#include <boost/chrono/duration.hpp>
int main() {
    // foo1(); // Will cause a memory leak
    foo2();
    foo3();
    foo3_const();

    // Give all the threads a chance to finish
    // Note: It is an awfull design, but it is OK
    // for example
    boost::this_thread::sleep_for(boost::chrono::seconds(2));

    boost::shared_ptr<foo_class> p(get_data());
    process1(p.get());
    process2(p.get());
    process3(p.get());
}

#include <cassert>

foo_class* get_data() {
    static int i = 0;
    ++ i;
    if (i % 2) {
        return new foo_class("Just some string");
    } else {
        return 0;
    }
}

void process1(const foo_class* p) {
    assert(p);
}

void process2(const foo_class* p) {
    assert(p);
}

void process3(const foo_class* p) {
    assert(p);
}

void process_str1(boost::shared_ptr<std::string> p) {
    assert(p);
}

void process_str2(const boost::shared_ptr<std::string>& p) {
    assert(p);
}

void process_cstr1(boost::shared_ptr<const std::string> p) {
    assert(p);
}

void process_cstr2(const boost::shared_ptr<const std::string>& p) {
    assert(p);
}


void process_sp1(const boost::shared_ptr<foo_class>& p) {
    assert(!!p);
}

void process_sp2(const boost::shared_ptr<foo_class>& p) {
    assert(!!p);
}

void process_sp3(const boost::shared_ptr<foo_class>& p) {
    assert(!!p);
}

