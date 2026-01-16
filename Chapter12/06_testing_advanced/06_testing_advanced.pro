if (!include(../../config.txt)) {
    error("Failed to open config.txt")
}

unix:DEFINES += BOOST_TEST_DYN_LINK=1

SOURCES += main.cpp foo.cpp developer1.cpp developer2.cpp
HEADERS += foo.hpp

!msvc:LIBS += -lboost_unit_test_framework $$BOOST_SYSTEM_LIBRARY
