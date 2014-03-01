#include <boost/program_options.hpp>
// 'reading_file' exception class is declared in errors.hpp
#include <boost/program_options/errors.hpp>
#include <iostream>

namespace opt = boost::program_options;

int main(int argc, char *argv[])
{
    opt::options_description desc("All options");

    // 'a' and 'o' are short option names for apples and oranges
    // 'name' option is not marked with 'required()', so user may
    // not support it
    desc.add_options()
        ("apples,a", opt::value<int>()->default_value(10), "how many apples do you have")
        ("oranges,o", opt::value<int>(), "how many oranges do you have")
        ("name", opt::value<std::string>(), "your name")
        ("help", "produce help message")
    ;

    opt::variables_map vm;

    // Parsing command line optioons and storing values to 'vm'
    opt::store(opt::parse_command_line(argc, argv, desc), vm);

    // We can also parse environment variables using 'parse_environment'
    // method
    opt::notify(vm);

    if (vm.count("help")) {
        std::cout << desc << "\n";
        return 1;
    }

    // Adding missing options from "aples_oranges.cfg" config file.
    // You can also provide an istreamable object as a first
    // parameter for 'parse_config_file'
    // 'char' template parameter will be passed to underlying
    // std::basic_istream object
    try {
        opt::store(opt::parse_config_file<char>("apples_oranges.cfg", desc), vm);
    } catch (const opt::reading_file& e) {
        std::cout << "Failed to open configuration file 'apples_oranges.cfg': "
                  << e.what();
    }
    opt::notify(vm);

    if (vm.count("name")) {
        std::cout << "Hi," << vm["name"].as<std::string>() << "!\n";
    }

    std::cout << "Fruits count: "
        << vm["apples"].as<int>() + vm["oranges"].as<int>()
        << std::endl;

    return 0;
}

