class operation {};

#include <vector>

class operation;

template <class T>
void execute_operations(const T&);

bool has_operation();
operation get_operation();

void process_transaction_1() {
    std::vector<operation> ops;
    ops.reserve(8); // TODO: Memory allocation. Not good!

    while (has_operation()) {
        ops.push_back(get_operation());
    }

    execute_operations(ops);
    // ...
}

#include <boost/container/small_vector.hpp>

void process_transaction_2() {
    boost::container::small_vector<operation, 8> ops;

    while (has_operation()) {
        ops.push_back(get_operation());
    }

    execute_operations(ops);
    // ...
}

namespace optimal {


void execute_operations(
    const boost::container::small_vector_base<operation>& ops
);

} // namespace optimal

void process_transaction_3() {
    boost::container::small_vector<operation, 8> ops;

    while (has_operation()) {
        ops.push_back(get_operation());
    }

    optimal::execute_operations(ops);
    // ...
}


int main() {
    process_transaction_1();
    process_transaction_2();
    process_transaction_3();
}


template <class T>
void execute_operations(const T& v) {
    assert(v.size() == 8);
}

void optimal::execute_operations(const boost::container::small_vector_base<operation>& ops) {
    assert(ops.size() == 8);
}

bool has_operation() {
    static int i = 0;
    return ++i % 9 != 0;
}

operation get_operation() {
    return operation();
}

void execute_operations(
    const boost::container::small_vector<operation, 4>&);

void execute_operations(
    const boost::container::small_vector<operation, 8>&);

void execute_operations(
    const boost::container::small_vector<operation, 16>&);

