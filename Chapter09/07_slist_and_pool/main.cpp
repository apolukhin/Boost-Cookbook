#include <boost/pool/pool_alloc.hpp>
#include <boost/container/slist.hpp>
#include <cassert>

typedef boost::fast_pool_allocator<int> allocator_t;
typedef boost::container::slist<int, allocator_t> slist_t;

void list_specific(slist_t& list, slist_t::iterator it) {
    typedef slist_t::iterator iterator;

    // Erasing element 776
    assert( *(++iterator(it)) == 776);
    assert(*it == 777);

    list.erase_after(it);

    assert(*it == 777);
    assert( *(++iterator(it)) == 775);

    list.clear();
    assert(list.empty());

    // Freeing memory: slist rebinds allocator_t and allocates
    // nodes of the slist, not just ints.

    boost::singleton_pool<
        boost::fast_pool_allocator_tag,
        sizeof(slist_t::stored_allocator_type::value_type)
    >::release_memory();
} // end of list_specific function

#include <list>
typedef std::list<int> stdlist_t;
void list_specific(stdlist_t& list, stdlist_t::iterator it) {
    // Erasing element 776
    ++it;
    assert( *it == 776);
    it = list.erase(it);
    assert(*it == 775);
}

template <class ListT>
void test_lists() {
    typedef ListT list_t;

    // Inserting 1000000 zeros.
    list_t  list(1000000, 0);

    for (int i = 0; i < 1000; ++i) {
        list.insert(list.begin(), i);
    }

    // Searching for some value.
    typedef typename list_t::iterator iterator;
    iterator it = std::find(list.begin(), list.end(), 777);
    assert(it != list.end());

    // Erasing some values.
    for (int i = 0; i < 100; ++i) {
        list.pop_front();
    }

    // Iterator is still valid and points to the same value.
    assert(it != list.end());
    assert(*it == 777);

    // Inserting more values
    for (int i = -100; i < 10; ++i) {
        list.insert(list.begin(), i);
    }

    // Iterator is still valid and points to the same value
    assert(it != list.end());
    assert(*it == 777);

    list_specific(list, it);
}

void test_slist() {
    test_lists<slist_t>();
}

void test_list() {
    test_lists<std::list<int> >();
}

#include <iostream>
int main(int argc, char* argv[]) {
    if (argc < 2) {
        test_slist();
        test_list();
        return 0;
    }

    switch(argv[1][0]) {
    case 's': std::cout << "slist_t:   "; test_slist(); break;
    case 'l': std::cout << "std::list: "; test_list();  break;
    default:
        std::cout << "Use 's' for testsing slist performance "
                     "and 'l' for testsing std::list performance.";
    }

    return 0;
}
