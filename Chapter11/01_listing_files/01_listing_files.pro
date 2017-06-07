if (!include(../../config.txt)) {
    error("Failed to open config.txt")
}

SOURCES += main.cpp
!msvc:LIBS += -lboost_system -lboost_filesystem
