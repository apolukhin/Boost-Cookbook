#include <boost/noncopyable.hpp>
#include <sstream>

class tasks_processor: boost::noncopyable {
    std::ostream& log_;

protected:
    virtual void do_process() = 0;

public:
    explicit tasks_processor(std::ostream& log)
        : log_(log)
    {}

    void process() {
        log_ << "Starting data processing";
        do_process();
    }
};

class fake_tasks_processor: public tasks_processor {
    std::ostringstream logger_;

    virtual void do_process() {
        logger_ << "Fake processor processed!";
    }

public:
    fake_tasks_processor()
        : tasks_processor(logger_) // Oops! logger_ does not exist here
        , logger_()
    {}

#ifdef NEWER_DEFINED1
    fake_tasks_processor()
        : logger_() // Oops! logger_ still will be constructed AFTER tasks_processor
        , tasks_processor(logger_)
    {}
#endif

};

#include <boost/utility/base_from_member.hpp>
class fake_tasks_processor_fixed
    : boost::base_from_member<std::ostringstream>
    , public tasks_processor
{
    typedef boost::base_from_member<std::ostringstream> logger_t;

    virtual void do_process() {
        logger_t::member << "Fake processor processed!";
    }

public:
    fake_tasks_processor_fixed()
        : logger_t()
        , tasks_processor(logger_t::member)
    {}
};

class fake_tasks_processor2
    : boost::base_from_member<std::ostringstream, 0>
    , boost::base_from_member<std::ostringstream, 1>
    , public tasks_processor
{

    typedef boost::base_from_member<std::ostringstream, 0> logger0_t;
    typedef boost::base_from_member<std::ostringstream, 1> logger1_t;

    virtual void do_process() {
        logger0_t::member << "0: Fake processor2 processed!";
        logger1_t::member << "1: Fake processor2 processed!";
    }

public:
    fake_tasks_processor2()
        : logger0_t()
        , logger1_t()
        , tasks_processor(logger0_t::member)
    {}
};


int main() {
    fake_tasks_processor_fixed tp;
    (void)tp;

    fake_tasks_processor2 tp2;
    (void)tp2;
}
