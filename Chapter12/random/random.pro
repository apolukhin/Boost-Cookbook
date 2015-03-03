if (!include(../../config.txt)) {
    error("Failed to open config.txt")
}

SOURCES += main.cpp
LIBS += -lboost_random -lboost_system
