//#include <something_that_defines_macros>

#if !defined(__clang__) \
    && !defined(__ICC) \
    && !defined(__INTEL_COMPILER) \
    && (defined(__GNUC__) || defined(__GNUG__))

// GCC specific

#endif

#include <boost/predef/compiler.h>

#if BOOST_COMP_GNUC

// GCC specific

#endif


#include <boost/predef/os.h>
#include <boost/predef/compiler.h>

#if BOOST_COMP_GNUC && BOOST_OS_LINUX && !BOOST_OS_ANDROID

// Do something for non Android Linux.

#endif

int main() {}
