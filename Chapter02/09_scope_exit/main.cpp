#include <boost/scope_exit.hpp>
#include <cstdlib>
#include <cstdio>
#include <cassert>

int main() {
    std::FILE* f = std::fopen("example_file.txt", "w");
    assert(f);
    BOOST_SCOPE_EXIT(f) {
    // Whatever happened in scope, this code will be executed
    // and file will be correctly closed.
        std::fclose(f);
    } BOOST_SCOPE_EXIT_END

    // Some code that may throw or return.
    // ...
}

class theres_more_example {
public:
    void close(std::FILE*);

    void theres_more_example_func() {
        std::FILE* f = 0;
        BOOST_SCOPE_EXIT(f, this_) { // Capture object `this_`.
            this_->close(f);
        } BOOST_SCOPE_EXIT_END
    }
};
