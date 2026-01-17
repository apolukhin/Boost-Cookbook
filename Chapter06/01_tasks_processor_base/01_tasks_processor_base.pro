if (!include(../../config.txt)) {
    error("Failed to open config.txt")
}

HEADERS += tasks_processor_base.hpp
SOURCES += main.cpp
!msvc {
    LIBS += $$BOOST_SYSTEM_LIBRARY -lboost_thread
    win32:LIBS += -lws2_32
}
