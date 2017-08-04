void unique_ptr_example();

#include <boost/scope_exit.hpp>
#include <cstdlib>
#include <cstdio>
#include <cassert>

int main() {
    std::FILE* f = std::fopen("example_file.txt", "w");
    assert(f);

    BOOST_SCOPE_EXIT(f) {
    // Whatever happened in outer scope, this code will be executed
    // and file will be correctly closed.
        std::fclose(f);
    } BOOST_SCOPE_EXIT_END

    // Some code that may throw or return.
    // ...

    unique_ptr_example();
}

class theres_more_example {
public:
    void close(std::FILE*);

    void func() {
        std::FILE* f = 0;
        BOOST_SCOPE_EXIT(f, this_) { // Capturing `this` as 'this_'
            this_->close(f);
        } BOOST_SCOPE_EXIT_END
    }
};


#include <boost/move/unique_ptr.hpp>
#include <cstdio>

void unique_ptr_example() {
    boost::movelib::unique_ptr<std::FILE, int(*)(std::FILE*)> f(
        std::fopen("example_file.txt", "w"), // open file
        &std::fclose  // specific deleter
    );
    // ...



    theres_more_example tme;
    tme.func();
}

#include <cassert>
void theres_more_example::close(std::FILE* f) { assert(!f); }

