if (!include(../../config.txt)) {
    error("Failed to open config.txt")
}

SOURCES += ../noncopyable_movable/main.cpp
QMAKE_CXXFLAGS += $$CPP11FLAG

