#include <string>
#include <stdexcept>
#include <cassert>

struct datetime {
    enum zone_offsets_t {
        OFFSET_NOT_SET,
        OFFSET_Z,
        OFFSET_UTC_PLUS,
        OFFSET_UTC_MINUS
    };

private:
    unsigned short year_;
    unsigned short month_;
    unsigned short day_;

    unsigned short hours_;
    unsigned short minutes_;
    unsigned short seconds_;


    zone_offsets_t zone_offset_type_;
    unsigned int zone_offset_in_min_;

    static void dt_assert(bool v, const char* msg) {
        if (!v) {
            throw std::logic_error(
                "Assertion failed in datetime: " + std::string(msg)
            );
        }
    }

public:
    datetime()
        : year_(0), month_(0), day_(0)
        , hours_(0), minutes_(0), seconds_(0)
        , zone_offset_type_(OFFSET_NOT_SET), zone_offset_in_min_(0)
    {}

    // Getters: year(), month(), day(), hours(), minutes(),
    // seconds(), zone_offset_type(), zone_offset_in_min()
    // ...
    unsigned short year() const { return year_; }
    unsigned short month() const { return month_; }
    unsigned short day() const { return day_; }

    unsigned short hours() const { return hours_; }
    unsigned short minutes() const { return minutes_; }
    unsigned short seconds() const { return seconds_; }

    zone_offsets_t zone_offset_type() const { return zone_offset_type_; }
    unsigned int zone_offset_in_min() const { return zone_offset_in_min_; }


    // Setters: set_year(unsigned short), set_day(unsigned short), ...
    //
    // void set_*(unsigned short v) {
    //     Some dt_assert.
    //     Setting the '*_' to 'v'.
    // }
    // ...
    void set_year(unsigned short val) {
        year_ = val;
    }

    void set_month(unsigned short val) {
        dt_assert(val < 13 && val > 0, "month parameter has incorrect value");
        month_ = val;
    }

    void set_day(unsigned short val)  {
        dt_assert(val < 32 && val > 0, "day parameter has incorrect value");
        day_ = val;
    }

    void set_hours(unsigned short val) {
        dt_assert(val < 24, "hours parameter has incorrect value");
        hours_ = val;
    }

    void set_minutes(unsigned short val) {
        dt_assert(val < 24, "minutes parameter has incorrect value");
        minutes_ = val;
    }

    void set_seconds(unsigned short val) {
        dt_assert(val < 60, "seconds parameter has incorrect value");
        seconds_ = val;
    }

    void set_zone_offset(zone_offsets_t val) {
        // We do not get over paranoid, so we won't check val range
        zone_offset_type_ = val;
    }

    void set_zone_offset_in_min(unsigned short val) {
        zone_offset_in_min_ = val;
    }
};

void set_zone_offset(datetime& dt, char sign, unsigned short hours
    , unsigned short minutes)
{
    dt.set_zone_offset(
        sign == '+'
        ? datetime::OFFSET_UTC_PLUS
        : datetime::OFFSET_UTC_MINUS
    );
    dt.set_zone_offset_in_min(hours * 60 + minutes);
}


// Default includes for Boost.Spirit.
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>

// We'll use bind() function from Boost.Spirit,
// because it interates better with parsers.
#include <boost/spirit/include/phoenix_bind.hpp>

datetime parse_datetime(const std::string& s) {
    using boost::spirit::qi::_1;
    using boost::spirit::qi::_2;
    using boost::spirit::qi::_3;
    using boost::spirit::qi::uint_parser;
    using boost::spirit::qi::char_;
    using boost::phoenix::bind;
    using boost::phoenix::ref;

    datetime ret;

    // Use unsigned short as output type; require Radix 10 and
    // from 2 to 2 digits.
    uint_parser<unsigned short, 10, 2, 2> u2_;

    // Use unsigned short as output type; require Radix 10 and
    // from 4 to 4 digits.
    uint_parser<unsigned short, 10, 4, 4> u4_;

    boost::spirit::qi::rule<const char*, void()> timezone_parser
        = -(  // unary minus means optional rule

            // Zero offset
            char_('Z')[ bind(
                &datetime::set_zone_offset, &ret, datetime::OFFSET_Z
            ) ]

            |  // OR

            // Specific zone offset
            ((char_('+')|char_('-')) >> u2_ >> ':' >> u2_) [
                bind(&set_zone_offset, ref(ret), _1, _2, _3)
            ]
        );

    boost::spirit::qi::rule<const char*, void()> date_parser =
           u4_ [ bind(&datetime::set_year, &ret, _1) ]  >> '-'
        >> u2_ [ bind(&datetime::set_month, &ret, _1) ] >> '-'
        >> u2_ [ bind(&datetime::set_day, &ret, _1) ];

    boost::spirit::qi::rule<const char*, void()> time_parser =
            u2_ [ bind(&datetime::set_hours, &ret, _1) ] >> ':'
         >> u2_ [ bind(&datetime::set_minutes, &ret, _1) ] >> ':'
         >> u2_ [ bind(&datetime::set_seconds, &ret, _1) ];

    const char* first = s.data();
    const char* const end = first + s.size();
    const bool success = boost::spirit::qi::parse(first, end,
        (
            (date_parser >> 'T' >> time_parser)
            | date_parser
            | time_parser
        )
        >> timezone_parser
    );

    if (!success || first != end) {
        throw std::logic_error("Parsing of '" + s + "' failed");
    }
    return ret;
} // end of parse_datetime() function


#include <boost/spirit/include/qi_rule.hpp>

// Somewhere in header file
class example_1 {
    boost::spirit::qi::rule<const char*, void()> some_rule_;
public:
    example_1();
};

// In source file
example_1::example_1() {
    some_rule_ = /* ... a lot of parser code ... */ boost::spirit::qi::char_('!');
}


int main () {
    datetime d1  = parse_datetime("2012-10-20T10:00:00Z");
    assert(d1.year() == 2012);
    assert(d1.month() == 10);
    assert(d1.day() == 20);
    assert(d1.hours() == 10);
    assert(d1.minutes() == 0);
    assert(d1.seconds() == 0);
    assert(d1.zone_offset_type() == datetime::OFFSET_Z);
    assert(d1.zone_offset_in_min() == 0);

    datetime d2  = parse_datetime("2012-10-20T10:00:00");
    assert(d2.year() == 2012);
    assert(d2.month() == 10);
    assert(d2.day() == 20);
    assert(d2.hours() == 10);
    assert(d2.minutes() == 0);
    assert(d2.seconds() == 0);
    assert(d2.zone_offset_type() == datetime::OFFSET_NOT_SET);
    assert(d2.zone_offset_in_min() == 0);

    datetime d3  = parse_datetime("2012-10-20T10:00:00+09:15");
    assert(d3.year() == 2012);
    assert(d3.month() == 10);
    assert(d3.day() == 20);
    assert(d3.hours() == 10);
    assert(d3.minutes() == 0);
    assert(d3.seconds() == 0);
    assert(d3.zone_offset_type() == datetime::OFFSET_UTC_PLUS);
    assert(d3.zone_offset_in_min() == 9 * 60 + 15);

    datetime d4  = parse_datetime("2012-10-20-09:15");
    assert(d4.year() == 2012);
    assert(d4.month() == 10);
    assert(d4.day() == 20);
    assert(d4.hours() == 0);
    assert(d4.minutes() == 0);
    assert(d4.seconds() == 0);
    assert(d4.zone_offset_type() == datetime::OFFSET_UTC_MINUS);
    assert(d4.zone_offset_in_min() == 9 * 60 + 15);

    datetime d5  = parse_datetime("10:00:09+09:15");
    assert(d5.year() == 0);
    assert(d5.month() == 0);
    assert(d5.day() == 0);
    assert(d5.hours() == 10);
    assert(d5.minutes() == 0);
    assert(d5.seconds() == 9);
    assert(d5.zone_offset_type() == datetime::OFFSET_UTC_PLUS);
    assert(d5.zone_offset_in_min() ==  9 * 60 + 15);
}

