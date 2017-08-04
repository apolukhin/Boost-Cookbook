#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <cassert>

struct date {
    unsigned short year;
    unsigned short month;
    unsigned short day;
};

// See recipe "Type 'reference to string'" for a better type
// than std::string for parameter 's'
date parse_date_time1(const std::string& s) {
    using boost::spirit::qi::_1;
    using boost::spirit::qi::ushort_;
    using boost::spirit::qi::char_;
    using boost::phoenix::ref;

    date res;
    const char* first = s.data();
    const char* const end = first + s.size();
    const bool success = boost::spirit::qi::parse(first, end,

        // Implementation of 'full-date' rule from EBNF grammar.
        ushort_[ ref(res.year) = _1 ] >> char_('-')
           >> ushort_[ ref(res.month) = _1 ] >> char_('-')
           >> ushort_[ ref(res.day) = _1 ]

    );

    if (!success || first != end) {
        throw std::logic_error("Parsing failed");
    }
    return res;
}

date parse_date_time2(const std::string& s) {
    using boost::spirit::qi::_1;
    using boost::spirit::qi::uint_parser;
    using boost::spirit::qi::char_;
    using boost::phoenix::ref;

    date res;

    // Use unsigned short as output type; require Radix 10 and
    // from 2 to 2 digits.
    uint_parser<unsigned short, 10, 2, 2> u2_;

    // Use unsigned short as output type; require Radix 10 and
    // from 4 to 4 digits.
    uint_parser<unsigned short, 10, 4, 4> u4_;

    const char* first = s.data();
    const char* const end = first + s.size();
    const bool success = boost::spirit::qi::parse(first, end,

        u4_ [ ref(res.year) = _1 ] >> char_('-')
            >> u2_ [ ref(res.month) = _1 ] >> char_('-')
            >> u2_ [ ref(res.day) = _1 ]

    );
    if (!success || first != end) {
        throw std::logic_error("Parsing failed");
    }
    return res;
}

#if !defined(BOOST_NO_CXX11_AUTO_DECLARATIONS) && !defined(BOOST_NO_CXX11_LAMBDAS)

date parse_date_time2_cxx(const std::string& s) {
    using boost::spirit::qi::uint_parser;
    using boost::spirit::qi::char_;

    date res;

    uint_parser<unsigned short, 10, 2, 2> u2_;
    uint_parser<unsigned short, 10, 4, 4> u4_;

    const auto y = [&res](unsigned short s) { res.year = s; };
    const auto m = [&res](unsigned short s) { res.month = s; };
    const auto d = [&res](unsigned short s) { res.day = s; };

    const char* first = s.data();
    const char* const end = first + s.size();
    const bool success = boost::spirit::qi::parse(first, end,
        u4_[y] >> char_('-') >> u2_[m] >> char_('-') >> u2_[d]
    );

    if (!success || first != end) {
        throw std::logic_error("Parsing failed");
    }
    return res;
}
#endif

int main() {
    {
    const date d = parse_date_time1("2017-12-31");
    assert(d.year == 2017);
    assert(d.month == 12);
    assert(d.day == 31);
    }

    {
    const date d = parse_date_time2("2017-11-21");
    assert(d.year == 2017);
    assert(d.month == 11);
    assert(d.day == 21);
    }

    try {
        parse_date_time2("12345-12-31");
        assert(false);
    }catch (const std::logic_error&) {}


#if !defined(BOOST_NO_CXX11_AUTO_DECLARATIONS) && !defined(BOOST_NO_CXX11_LAMBDAS)
    {
    const date d = parse_date_time2_cxx("1988-10-09");
    assert(d.year == 1988);
    assert(d.month == 10);
    assert(d.day == 9);
    }
#endif

}
