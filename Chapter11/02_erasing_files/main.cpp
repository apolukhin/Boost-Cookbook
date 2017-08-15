#include <boost/config.hpp>
#ifdef BOOST_MSVC // Workaround for https://svn.boost.org/trac10/ticket/13135
#   define NDEBUG 1
#endif

#include <boost/filesystem/operations.hpp>
#include <cassert>
#include <fstream>
#include <iostream>

int main() {
    boost::system::error_code error;

    boost::filesystem::create_directories("dir/subdir", error);
    assert(!error);

    std::ofstream ofs("dir/subdir/file.txt");
    ofs << "Boost.Filesystem is fun!";
    assert(ofs);
    ofs.close();

    boost::filesystem::create_symlink(
        "dir/subdir/file.txt", "symlink", error);

    if (!error) {
        std::cerr << "Symlink created\n";
        assert(boost::filesystem::exists("symlink"));
    } else {
        std::cerr << "Failed to create a symlink\n";

        boost::filesystem::remove_all("dir", error);
        assert(!error);

        boost::filesystem::remove("symlink", error);
        assert(!error);
    } /*if (!error)*/
} /*main*/
