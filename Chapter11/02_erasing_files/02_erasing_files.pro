if (!include(../../config.txt)) {
    error("Failed to open config.txt")
}

SOURCES += main.cpp
!msvc:LIBS += $$BOOST_SYSTEM_LIBRARY -lboost_filesystem
