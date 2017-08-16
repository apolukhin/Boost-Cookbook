#include <boost/interprocess/file_mapping.hpp>
#include <boost/interprocess/mapped_region.hpp>

#include <fstream>
#include <cassert>
#include <iostream>
#include <iterator>
#include <algorithm>

int main(int argc, char* argv[]) {
    static const std::size_t filesize = 1024 * 1024 /** 128*/;
    const char filename[] = "test_file.txt";

    assert(argc >= 2); // Run with c,m,r or a parameter: ./this_program c
    switch (argv[1][0]) {
    case 'c': {
        // Not effective, but this is not a place that we measure
        std::ofstream f(filename, std::ofstream::binary);
        std::fill_n(
            std::ostream_iterator<char>(f),
            filesize - 1,
            '\3'
        );

        f << '\1';
    }
    break;

    case 'm': {
        std::cout << "mapped_region:";
        const boost::interprocess::mode_t mode = boost::interprocess::read_only;
        boost::interprocess::file_mapping fm(filename, mode);
        boost::interprocess::mapped_region region(fm, mode, 0, 0);
        //region.advise(boost::interprocess::mapped_region::advice_sequential);

        const char* begin = static_cast<const char*>(
            region.get_address()
        );
        const char* pos = std::find(
            begin, begin + region.get_size(), '\1'
        );
        assert(pos == begin + filesize - 1);
        assert(region.get_size() == filesize);
    }
    break;

    case 'r': {
        std::cout << "ifstream:";
        static const std::size_t kilobyte = 1024;
        std::ifstream f(filename, std::ifstream::binary);
        char c[kilobyte];
        char* begin = c;
        char* end = c + sizeof(c);
        char* pos;

        size_t i = 0;
        for (; i < filesize / kilobyte; ++i) {
            f.read(c, kilobyte);
            pos = std::find(begin, end, '\1');
            if (pos != end) {
                break;
            }
        }

        assert(pos - begin == kilobyte - 1);
        assert(i == filesize / kilobyte - 1);
    }
    break;

    case 'a': {
        std::cout << "C:";
        static const std::size_t kilobyte = 1024;
        FILE* f = fopen(filename, "rb");
        char c[kilobyte];
        char* begin = c;
        char* end = c + sizeof(c);
        char* pos;

        size_t i = 0;
        for (; i < filesize / kilobyte; ++i) {
            std::size_t res = fread(c, 1, kilobyte, f);
            pos = std::find(begin, end, '\1');
            if (pos != end) {
                break;
            }
            (void)res;
        }

        assert(pos - begin == kilobyte - 1);
        assert(i == filesize / kilobyte - 1);
        fclose (f);
    }
    break;

    default:
        return 42;
    }
}
