if (!include(../../config.txt)) {
    error("Failed to open config.txt")
}

SOURCES += ../move/main.cpp
QMAKE_CXXFLAGS += $$CPP11FLAG

