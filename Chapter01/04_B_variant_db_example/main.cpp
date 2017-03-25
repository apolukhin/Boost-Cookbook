#include <boost/variant.hpp>
#include <vector>
#include <string>
#include <iostream>

// This typedefs and methods will be in header,
// that wraps around native SQL interface.
typedef boost::variant<int, float, std::string> cell_t;
typedef std::vector<cell_t> db_row_t;

// This is just an example, no actual work with database.
db_row_t get_row(const char* /*query*/) {
    // See recipe "Type 'reference to string'"
    // for a better type for 'query' parameter.
    db_row_t row;
    row.push_back(10);
    row.push_back(10.1f);
    row.push_back("hello again");
    return row;
}

// This is how code required to sum values
// We can provide no template parameter
// to boost::static_visitor<> if our visitor returns nothing.
struct db_sum_visitor: public boost::static_visitor<double> {
    double operator()(int value) const {
        return value;
    }
    double operator()(float value) const {
        return value;
    }
    double operator()(const std::string& /*value*/) const {
        return 0.0;
    }
};

int main() {
    db_row_t row = get_row("Query: Give me some row, please.");
    double res = 0.0;
    for (db_row_t::const_iterator it = row.begin(), end = row.end(); it != end; ++it) {
        res += boost::apply_visitor(db_sum_visitor(), *it);
    }
    std::cout << "Sum of arithmetic types in database row is: " << res << std::endl;
}
