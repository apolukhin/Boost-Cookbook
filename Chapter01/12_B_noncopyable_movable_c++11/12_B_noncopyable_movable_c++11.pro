if (!include(../../config.txt)) {
    error("Failed to open config.txt")
}

SOURCES += ../12_A_noncopyable_movable/main.cpp
QMAKE_CXXFLAGS += $$CPP11FLAG

