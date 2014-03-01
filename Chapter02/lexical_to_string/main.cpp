#include <assert.h>
#include <boost/lexical_cast.hpp>

void foo1() {
    std::string s = boost::lexical_cast<std::string>(100);
    assert(s == "100");
}

#include <sstream>
void foo2() {
    // C++ way of converting to strings
    std::stringstream ss;
    ss << 100;
    std::string s;
    ss >> s;
    // Variable 'ss' will dangle all the way, till the end of scope
    // Multiple virtual methods were called during conversion
    assert(s == "100");
}

#include <cstdlib>
void foo3() {
    // C way of converting to strings
    char buffer[100];
    std::sprintf(buffer, "%i", 100);
    // You will need an unsigned long long int type to count how many
    // times errors were made in 'printf' like functions all around the
    // world. 'printf' functions are a constant security threat!
    // But wait, we still need to construct a std::string
    std::string s(buffer);
    // And now we have an buffer variable that won't be used
    assert(s == "100");
}

#include <boost/noncopyable.hpp>
#include <boost/tuple/tuple.hpp>
#include <algorithm>

namespace vendor1 {

class control_console: private boost::noncopyable {
public:
    enum command_t {
        MOVE = 0,// move manitulator
        TURN_CLOCKWISE = 1, // turn manitulator clockwise
        TURN_COUNTER_CLOCKWISE = 2 // turn manitulator counter clockwise
    };

typedef boost::tuple<command_t, unsigned short, unsigned short> data_t;

private:
    control_console(); // Non constructible class
    static bool get_data(data_t& out);

public:

    template <class FuncT>
    static void handle_data(FuncT f) {
        data_t data;
        while (get_data(data)) {
            f(data);
        }
    }
};

bool control_console::get_data(control_console::data_t& out) {
    static int i = 0;

    if (i == 0) {
        out = boost::make_tuple(control_console::MOVE, static_cast<unsigned short>(100), static_cast<unsigned short>(100));
    } else if (i == 1) {
        out = boost::make_tuple(control_console::TURN_CLOCKWISE, static_cast<unsigned short>(10), static_cast<unsigned short>(0));
    } else if (i == 2) {
        out = boost::make_tuple(control_console::TURN_COUNTER_CLOCKWISE, static_cast<unsigned short>(190), static_cast<unsigned short>(0));
    } else {
        return false;
    }

    ++ i;
    return true;
}

}

namespace vendor2 {

namespace robot {
    // COMMANDS:
    // "clws" - turn manitulator clockwise
    // "move" - move manitulator
    // "cclo" - turn manitulator counter clockwise

    typedef boost::array<char, 512> command_t;
    void accept_command(const command_t& comnd) {
        // do something

        static int i = 0;
        if (i == 0) {
            assert(!std::strcmp(&comnd[0], "move 100 100"));
        } else if (i == 1) {
            assert(!std::strcmp(&comnd[0], "clws 10"));
        } else if (i == 2) {
            assert(!std::strcmp(&comnd[0], "cclo 190"));
        }

        ++ i;
    }
}

}

namespace your_project {
    typedef vendor1::control_console::data_t data_t;

    namespace detail {
        static const std::size_t buffer_size
            = 5 /*maximum value representable by unsigned short is 65535*/
            + 1; /* place for a '\0' symbol*/

        // If boost::array or std::array passed to boost::lexical_cast as
        // as output parameter type, lexical_cast won't construct std::string,
        // so no heap allocation will occur in string constructor
        typedef boost::array<char, buffer_size> num_data_buffer_t;

        void move_impl(vendor2::robot::command_t& command, unsigned short x, unsigned short y) {
            char* it = &command[0];
            const boost::array<char, 6> move_word = {{"move "}};
            // '-1' required because we do not whant to write '\0' char
            it = std::copy(move_word.begin(), move_word.end() - 1, it);

            // X Coordinate
            const num_data_buffer_t converted_x_value
                    = boost::lexical_cast<num_data_buffer_t>(x);
            const std::size_t converted_x_len = std::strlen(converted_x_value.cbegin());
            it = std::copy(converted_x_value.cbegin(), converted_x_value.cbegin() + converted_x_len, it);

            // Whitespace between X and Y coordinates
            *it = ' ';
            ++it;

            // Y Coordinate
            const num_data_buffer_t converted_y_value
                    = boost::lexical_cast<num_data_buffer_t>(y);
            std::copy(converted_y_value.cbegin(), converted_y_value.cend(), it);
        }

        void clockwise_impl(vendor2::robot::command_t& command, unsigned short degree) {
            char* it = &command[0];
            const boost::array<char, 6> clws_word = {{"clws "}};
            // '-1' required because we do not whant to write '\0' char
            it = std::copy(clws_word.begin(), clws_word.end() - 1, it);

            // Degree
            const num_data_buffer_t converted_degree_value
                    = boost::lexical_cast<num_data_buffer_t>(degree);
            std::copy(converted_degree_value.cbegin(), converted_degree_value.cend(), it);
        }

        void counter_clockwise_impl(vendor2::robot::command_t& command, unsigned short degree) {
            char* it = &command[0];
            const boost::array<char, 6> cclo_word = {{"cclo "}};
            // '-1' required because we do not whant to write '\0' char
            it = std::copy(cclo_word.begin(), cclo_word.end() - 1, it);

            // Degree
            const num_data_buffer_t converted_degree_value
                    = boost::lexical_cast<num_data_buffer_t>(degree);
            std::copy(converted_degree_value.cbegin(), converted_degree_value.cend(), it);
        }
    }


    void accept_and_send_data(const data_t& data) {
        typedef vendor1::control_console enum_vals_t;
        vendor2::robot::command_t command;

        switch (boost::get<0>(data)) {
        case enum_vals_t::MOVE:
            detail::move_impl(command, boost::get<1>(data), boost::get<2>(data));
            break;

        case enum_vals_t::TURN_CLOCKWISE:
            detail::clockwise_impl(command, boost::get<1>(data));
            break;

        case enum_vals_t::TURN_COUNTER_CLOCKWISE:
            detail::counter_clockwise_impl(command, boost::get<1>(data));
            break;
        }

        vendor2::robot::accept_command(command);
    }
}


int main() {
    foo1();
    foo2();
    foo3();

    vendor1::control_console::handle_data(&your_project::accept_and_send_data);
}
