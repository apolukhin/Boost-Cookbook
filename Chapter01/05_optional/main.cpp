#include <boost/optional.hpp>
#include <iostream>
#include <stdlib.h>

class locked_device {
    explicit locked_device(const char* /*param*/) {
        // We have unique access to device
        std::cout << "Device is locked\n";
    }

public:
    ~locked_device () {
        // Releasing device lock
    }

    void use() {
        std::cout << "Success!\n";
    }

    static boost::optional<locked_device> try_lock_device() {
        if (rand() % 2) {
            // Failed to lock device
            return boost::none;
        }
        // Success!
        return locked_device("device name");
    }
};

int main() {
    // Boost has a library called Random. If you wonder why it was
    // written when stdlib.h has rand() function, see recipes
    // 'Random distribution' and 'Making a random generator'.
    srand(5);

    for (unsigned i = 0; i < 10; ++i) {
        boost::optional<locked_device> t = locked_device::try_lock_device();
        // optional is convertible to bool
        if (t) {
            t->use();
            return 0;
        } else {
            std::cout << "...trying again\n";
        }
    }

    std::cout << "Failure!\n";
    return -1;
}
