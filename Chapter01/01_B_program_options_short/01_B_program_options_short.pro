if (!include(../../config.txt)) {
    error("Failed to open config.txt")
}

LIBS += -lboost_program_options

SOURCES += main.cpp

include(apples_oranges.cfg)

