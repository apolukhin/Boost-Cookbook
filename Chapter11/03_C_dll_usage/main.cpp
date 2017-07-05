#include <cassert>

#include <boost/dll/shared_library.hpp>
#include <iostream>

int main(int argc, char* argv[]) {
    assert(argc == 2);
    boost::filesystem::path plugin_path = argv[1];

    boost::dll::shared_library plugin(
        plugin_path,
        boost::dll::load_mode::append_decorations
    );

    auto greeter = plugin.get<std::string(const std::string&)>("greeter");
    std::cout << greeter("Sally Sparrow");
}
