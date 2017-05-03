if (!include(../../config.txt)) {
    error("Failed to open config.txt")
}

QMAKE_CXXFLAGS += $$CPP11FLAG
SOURCES += main.cpp
LIBS += -lboost_thread -lboost_system
