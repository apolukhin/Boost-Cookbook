if (!include(../../config.txt)) {
    error("Failed to open config.txt")
}

HEADERS += tasks_processor_base.hpp
SOURCES += main.cpp
!msvc:LIBS += -lboost_system -lboost_thread
