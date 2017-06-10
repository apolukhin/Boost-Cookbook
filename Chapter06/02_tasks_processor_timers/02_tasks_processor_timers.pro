if (!include(../../config.txt)) {
    error("Failed to open config.txt")
}


HEADERS += \
    ../01_tasks_processor_base/tasks_processor_base.hpp \
    tasks_processor_timers.hpp

SOURCES += main.cpp
QMAKE_CXXFLAGS += $$CPP11FLAG
!msvc {
    LIBS += -lboost_system -lboost_thread
    win32:LIBS += -lws2_32
}
