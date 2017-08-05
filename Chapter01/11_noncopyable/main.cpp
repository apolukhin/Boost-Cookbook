class descriptor_owner {
    void* descriptor_;

public:
    explicit descriptor_owner(const char* params);

    ~descriptor_owner() {
        // system_api_free_descriptor(descriptor_);
    }
};

descriptor_owner::descriptor_owner(const char* ){}


void i_am_bad() {
    descriptor_owner d1("O_o");
    descriptor_owner d2("^_^");

    // Descriptor of d2 was not correctly freed
    d2 = d1;

    // destructor of d2 will free the descriptor
    // destructor of d1 will try to free already freed descriptor
}

#include <boost/noncopyable.hpp>

class descriptor_owner_fixed : private boost::noncopyable {
    // ...
public:
    descriptor_owner_fixed(const char* params){ (void)params; }
};

void i_am_good() {
    descriptor_owner_fixed d1("O_o");
    descriptor_owner_fixed d2("^_^");

    // Won't compile
    //d2 = d1;
    //descriptor_owner_fixed d3(d1);
}


int main() {
    i_am_bad();
    i_am_good();
}

