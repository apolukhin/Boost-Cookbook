#include <boost/optional.hpp>
#include <iostream>

class locked_device {
    explicit locked_device(const char* /*param*/) {
        // We have unique access to device.
        std::cout << "Device is locked\n";
    }

    static bool try_lock_device_impl();
public:
    void use() {
        std::cout << "Success!\n";
    }

    static boost::optional<locked_device> try_lock_device() {
        if (!try_lock_device_impl()) {
            // Failed to lock device.
            return boost::none;
        }

        // Success!
        return locked_device("device name");
    }

    ~locked_device(); // Releases device lock.
};

int main() {
    for (unsigned i = 0; i < 10; ++i) {
        boost::optional<locked_device> t
            = locked_device::try_lock_device();
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

// details:

locked_device::~locked_device(){}

bool locked_device::try_lock_device_impl() {
    static int i = 0;
    ++i;
    return i == 3;
}
