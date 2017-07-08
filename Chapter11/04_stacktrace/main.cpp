#include <iostream>
#include <boost/stacktrace.hpp>

void report_bankruptcy() {
    std::cout << "Sorry, you're bankrupt!\n";
    std::cout << "Here's how it happened:\n" << boost::stacktrace::stacktrace();
    std::exit(0);
}

BOOST_NOINLINE void start_trading(int money);

int main() {
    int money = 1000;
    start_trading(money);
}

// details:

// Note: BOOST_NOINLINE and BOOST_FORCEINLINE are used for a more nice output.
// Do not use them in production code without super extremely high need.

// 99% precise HFT simulator:

BOOST_NOINLINE void make_a_bet(int money);
BOOST_FORCEINLINE int party(int money);
BOOST_NOINLINE void win(int money);



BOOST_NOINLINE void loose(int money) {
    if (money < 10) {
        report_bankruptcy();
    }
    make_a_bet(money);
}

BOOST_NOINLINE int go_to_casino(int money) {
    static bool i = true;
    if (i) {
        // First time in casin0 :)
        i = false;
        win(money * 2);
    }
    money *= 0.00000003; // Lucky day in a casino! Not all the money are lost.
    loose(money);
    return party(money);
}

BOOST_NOINLINE int go_to_bar(int money) {
    money -= 11; // 1 beer please ...
    money -= 11 * 20; // ... and 1 beer to everyone in the room!
    return party(money);
}

BOOST_FORCEINLINE int party(int money) {
    if (money > 0) {
        return money & 1 ? go_to_casino(money) : go_to_bar(money);
    }

    report_bankruptcy();
    return 0;
}

BOOST_NOINLINE void win(int money) {
    money = party(money);
    make_a_bet(money);
}

BOOST_NOINLINE void make_a_bet(int money) {
    static int i = 3;
    -- i;
    if (!i) {
        i = 3;
        win(money * 100500);
    } else {
        loose(money * 0.9);
    }
}

BOOST_NOINLINE void start_trading(int money) {
    make_a_bet(money);
}
