if (!include(../../config.txt)) {
    error("Failed to open config.txt")
}

SOURCES += main.cpp
!msvc:LIBS += -lboost_thread $$BOOST_SYSTEM_LIBRARY
