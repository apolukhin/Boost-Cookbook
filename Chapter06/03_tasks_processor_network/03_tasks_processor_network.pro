if (!include(../../config.txt)) {
    error("Failed to open config.txt")
}

HEADERS += \
    ../01_tasks_processor_base/tasks_processor_base.hpp \
    ../02_tasks_processor_timers/tasks_processor_timers.hpp \
    tasks_processor_network.hpp

SOURCES += main.cpp
QMAKE_CXXFLAGS += $$CPP11FLAG
!msvc:LIBS += -lboost_thread -lboost_system
