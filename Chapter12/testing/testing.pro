if (!include(../../config.txt)) {
    error("Failed to open config.txt")
}

DEFINES += BOOST_TEST_DYN_LINK=1
SOURCES += main.cpp

LIBS += -lboost_unit_test_framework -lboost_system
