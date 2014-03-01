#include <boost/filesystem/operations.hpp>
#include <iostream>

int main() {
    boost::filesystem::directory_iterator begin("./");
    boost::filesystem::directory_iterator end;

    for (; begin != end; ++ begin) {
        /*
        boost::filesystem::file_status fs =
            boost::filesystem::status(*begin);
        */

        boost::filesystem::file_status fs = 
            begin->status();

        switch (fs.type()) {
        case boost::filesystem::regular_file:
            std::cout << "FILE       "; 
            break;
        case boost::filesystem::symlink_file:
            std::cout << "SYMLINK    "; 
            break;
        case boost::filesystem::directory_file:
            std::cout << "DIRECTORY  "; 
            break;
        default:
            std::cout << "OTHER      "; 
            break;
        }

        if (fs.permissions() & boost::filesystem::owner_write) {
            std::cout << "W ";
        } else {
            std::cout << "  ";
        }

        std::cout << begin->path() << '\n';
        //std::cout << *begin << '\n';
    } /*for*/
} /*main*/
