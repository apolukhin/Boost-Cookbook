if (!include(../../config.txt)) {
    error("Failed to open config.txt")
}

SOURCES += main.cpp
msvc {
    LIBS += -llibboost_timer
} else {
    LIBS += -lboost_timer -lboost_chrono -lboost_system
}
