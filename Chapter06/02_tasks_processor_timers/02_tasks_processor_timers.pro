if (!include(../../config.txt)) {
    error("Failed to open config.txt")
}


HEADERS += \
    ../01_tasks_processor_base/tasks_processor_base.hpp \
    tasks_processor_timers.hpp

SOURCES += main.cpp
!msvc:LIBS += -lboost_system -lboost_thread
