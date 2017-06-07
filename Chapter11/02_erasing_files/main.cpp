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

    boost::filesystem::create_directory_symlink("dir/subdir", "symlink", error);
    if (!error) {
        std::cerr << "Symlink created\n";
        assert(boost::filesystem::exists("symlink/file.txt"));
    } else {
        std::cerr << "Failed to create a symlink\n";
        boost::filesystem::remove("dir/subdir/file.txt", error);
        assert(!error);
    } /*if (!error)*/
} /*main*/
