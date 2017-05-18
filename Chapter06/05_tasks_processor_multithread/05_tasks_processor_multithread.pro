if (!include(../../config.txt)) {
    error("Failed to open config.txt")
}

HEADERS += \
    ../01_tasks_processor_base/tasks_processor_base.hpp \
    ../02_tasks_processor_timers/tasks_processor_timers.hpp \
    ../03_tasks_processor_network/tasks_processor_network.hpp \
    tasks_processor_multithread.hpp


SOURCES += main.cpp
!msvc:LIBS += -lboost_thread -lboost_system
