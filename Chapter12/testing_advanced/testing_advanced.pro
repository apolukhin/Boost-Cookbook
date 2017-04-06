if (!include(../../config.txt)) {
    error("Failed to open config.txt")
}

SOURCES += main.cpp foo.cpp developer1.cpp developer2.cpp
HEADERS += foo.hpp

DEFINES += BOOST_TEST_DYN_LINK=1
LIBS += -lboost_unit_test_framework -lboost_system
