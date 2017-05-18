if (!include(../../config.txt)) {
    error("Failed to open config.txt")
}

QMAKE_CXXFLAGS += $$CPP11FLAG
SOURCES += main.cpp
!msvc:LIBS += -lboost_thread -lboost_system
