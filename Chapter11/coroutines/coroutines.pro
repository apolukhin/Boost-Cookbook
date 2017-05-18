if (!include(../../config.txt)) {
    error("Failed to open config.txt")
}

SOURCES += main.cpp

!msvc:LIBS += -lboost_context
!msvc:LIBS += -lboost_coroutine -lboost_thread -lboost_system
