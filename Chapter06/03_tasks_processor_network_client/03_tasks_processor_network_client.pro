if (!include(../../config.txt)) {
    error("Failed to open config.txt")
}

# We are NOT building an executable
TEMPLATE -= app

# ... we are building a library.
TEMPLATE = lib

HEADERS += \
    ../01_tasks_processor_base/tasks_processor_base.hpp \
    ../02_tasks_processor_timers/tasks_processor_timers.hpp \
    tasks_processor_network_client.hpp

SOURCES += client.cpp
QMAKE_CXXFLAGS += $$CPP11FLAG
!msvc {
    LIBS += -lboost_system -lboost_thread
    win32:LIBS += -lws2_32 -lwsock32
}
