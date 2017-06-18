if (!include(../../config.txt)) {
    error("Failed to open config.txt")
}

SOURCES += main.cpp
LIBS += -lboost_timer
!msvc:LIBS += -lboost_chrono -lboost_system
