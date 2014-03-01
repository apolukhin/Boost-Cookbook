if (!include(../../config.txt)) {
    error("Failed to open config.txt")
}

SOURCES += main.cpp header.hpp source.cpp
QMAKE_CXXFLAGS += $$CPP11FLAG
