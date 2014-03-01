if (!include(../../config.txt)) {
    error("Failed to open config.txt")
}


HEADERS += \
    ../tasks_processor_base/tasks_processor_base.hpp \
    tasks_processor_timers.hpp

SOURCES += main.cpp
LIBS += -lboost_system -lboost_thread
