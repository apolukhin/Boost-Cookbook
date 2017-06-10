if (!include(../../config.txt)) {
    error("Failed to open config.txt")
}

HEADERS += \
    ../01_tasks_processor_base/tasks_processor_base.hpp \
    ../02_tasks_processor_timers/tasks_processor_timers.hpp \
    ../03_tasks_processor_network_client/tasks_processor_network_client.hpp \
    ../04_tasks_processor_network_accept/tasks_processor_network_accept.hpp \
    tasks_processor_multithread.hpp


SOURCES += main.cpp
QMAKE_CXXFLAGS += $$CPP11FLAG
!msvc {
    LIBS += -lboost_system -lboost_thread
    win32:LIBS += -lws2_32 -lwsock32
}
