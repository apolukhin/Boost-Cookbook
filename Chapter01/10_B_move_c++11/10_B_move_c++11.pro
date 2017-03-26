if (!include(../../config.txt)) {
    error("Failed to open config.txt")
}

SOURCES += ../10_A_move/main.cpp
QMAKE_CXXFLAGS += $$CPP11FLAG

