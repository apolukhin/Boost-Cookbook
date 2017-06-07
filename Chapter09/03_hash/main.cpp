#include <string>

template <class T>
std::size_t test_default() {
    // Constants
    const std::size_t ii_max = 200000000;
    const std::string s(
        "Long long long string that "
        "will be used in tests to compare "
        "speed of equality comparisons."
    );
    
    // Making some data, that will be 
    // used in comparisons
    const T data1[] = {
        T(s),
        T(s + s),
        T(s + ". Whooohooo"),
        T(std::string(""))
    };

    const T data2[] = {
        T(s),
        T(s + s),
        T(s + ". Whooohooo"),
        T(std::string(""))
    };

    const std::size_t data_dimensions = sizeof(data1) / sizeof(data1[0]);

    std::size_t matches = 0u;
    for (std::size_t ii = 0; ii < ii_max; ++ii) {
        for (std::size_t i = 0; i < data_dimensions; ++i) {
            for (std::size_t j = 0; j < data_dimensions; ++j) {
                if (data1[i] == data2[j]) {
                    ++ matches;
                }
            }
        }
    }

    return matches;
}




#include <boost/functional/hash.hpp>

struct string_hash_fast {
    typedef std::size_t comp_type;

    const comp_type     comparison_;
    const std::string   str_;

    explicit string_hash_fast(const std::string& s)
        : comparison_(
            boost::hash<std::string>()(s)
        )
        , str_(s)
    {}
};

inline bool operator == (const string_hash_fast& s1, const string_hash_fast& s2) {
    return s1.comparison_ == s2.comparison_ && s1.str_ == s2.str_;
}

inline bool operator != (const string_hash_fast& s1, const string_hash_fast& s2) {
    return !(s1 == s2);
}

// Shall be in namespace of string_hash_fast class
inline std::size_t hash_value(const string_hash_fast& v) {
    return v.comparison_;
}

#include <iostream>
int main(int argc, char* argv[]) {
    if (argc < 2) {
        assert(
            test_default<string_hash_fast>()
            ==
            test_default<std::string>()
        );
        return 0;
    }

    switch (argv[1][0]) {
    case 'h':
        std::cout << "HASH matched: "
                  << test_default<string_hash_fast>();
        break;
    case 's':
        std::cout << "STD matched: "
                  << test_default<std::string>();
        break;
    default:
        assert(false);
        return -2;
    }

    std::cout << '\n';
    assert(
        boost::hash<string_hash_fast>()(string_hash_fast("test"))
        ==
        boost::hash<std::string>()("test")
    );
}

