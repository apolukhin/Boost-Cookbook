#include <boost/any.hpp>
#include <vector>
#include <string>
#include <typeinfo>
#include <algorithm>
#include <iostream>

// This typedefs and methods will be in our header,
// that wraps around native SQL interface
typedef boost::any cell_t;
typedef std::vector<cell_t> db_row_t;

// This is just an example, no actual work with database.
db_row_t get_row(const char* /*query*/) {
    // In real application 'query' parameter shall have a 'const
    // char*' or 'const std::string&' type? See recipe "Type
    // 'reference to string'" for an answer.
    db_row_t row;
    row.push_back(10);
    row.push_back(10.1f);
    row.push_back(std::string("hello again"));
    return row;
}

// This is how a user will use your classes
struct db_sum: public std::unary_function<boost::any, void> {
private:
    double& sum_;

public:
    explicit db_sum(double& sum)
        : sum_(sum)
    {}

    void operator()(const cell_t& value) {
        const std::type_info& ti = value.type();
        if (ti == typeid(int)) {
            sum_ += boost::any_cast<int>(value);
        } else if (ti == typeid(float)) {
            sum_ += boost::any_cast<float>(value);
        }
    }
};

int main() {
    db_row_t row = get_row("Query: Give me some row, please.");
    double res = 0.0;
    std::for_each(row.begin(), row.end(), db_sum(res));
    std::cout << "Sum of arithmetic types in database row is: " << res << std::endl;
}
