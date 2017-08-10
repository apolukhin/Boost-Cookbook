#include <vector>
#include <string>

// Executes for a long time.
std::vector<std::string> read_defaults();

namespace first_attempt {

struct postprocessor {
    typedef std::vector<std::string> answer_t;

    // Concurrent calls on the same variable are safe.
    answer_t act(const std::string& in) const {
        if (in.empty()) {
            // Extremely rare condition.
            return read_defaults();
        }

        // ...
        answer_t ret;
        return ret;
    }
};

} // namespace first_attempt

namespace second_attempt {

struct postprocessor {
    typedef std::vector<std::string> answer_t;

private:
    answer_t default_;

public:
    postprocessor()
        : default_(read_defaults())
    {}

    // Concurrent calls on the same variable are safe.
    answer_t act(const std::string& in) const {
        if (in.empty()) {
            // Extremely rare condition.
            return default_;
        }

        // ...
        answer_t ret;
        return ret;
    }
};

} // namespace second_attempt




#include <boost/thread/once.hpp>

namespace right_solution {

struct postprocessor {
    typedef std::vector<std::string> answer_t;

private:
    mutable boost::once_flag    default_flag_;
    mutable answer_t            default_;

public:
    postprocessor()
        : default_flag_(BOOST_ONCE_INIT)
        , default_()
    {}

    // Concurrent calls on the same variable are safe.
    answer_t act(const std::string& in) const {
        answer_t ret;
        if (in.empty()) {
            // Extremely rare condition.
            boost::call_once(default_flag_, [this]() {
                this->default_ = read_defaults();
            });
            return default_;
        }

        // ...
        return ret;
    }
};

} // namespace right_solution

#include <iostream>
void once_printer(int i) {
    static boost::once_flag flag = BOOST_ONCE_INIT;
    boost::call_once(
        flag,
        [](int v) { std::cout << "Print once " << v << '\n'; },
        i // <=== Passed to lambda from above.
    );

    // ...
}


#include <cassert>
int main() {
    right_solution::postprocessor pp;
    assert(pp.act(std::string()).size() == 5);
    assert(pp.act("Hello").size() == 0);

    for (unsigned i = 0; i < 10; ++i) {
        once_printer(i);
    }
}

// Details:

std::vector<std::string> read_defaults() {
    std::vector<std::string> ret  {
        "Do", "not", "look", "at", "me"
    };
    return ret;
}
