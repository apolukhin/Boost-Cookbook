#include <boost/math/special_functions.hpp>
#include <cassert>

template <class T>
void check_float_inputs(T value) {
    assert(!boost::math::isinf(value));
    assert(!boost::math::isnan(value));

    if (boost::math::signbit(value)) {
        value = boost::math::changesign(value);
    }

    // ...
    assert(value + (std::numeric_limits<T>::epsilon)() >= static_cast<T>(0));
} // check_float_inputs

int main() {
    check_float_inputs(0.0);
    check_float_inputs(-110.0f);
    check_float_inputs(-11.0l);

    // Shall fail the `!boost::math::isinf(value)` assertion
    //check_float_inputs((std::numeric_limits<double>::max)() * 2.0);


    // Shall fail the `!boost::math::isnan(value)` assertion
    //check_float_inputs(std::sqrt(-1.0));
}
