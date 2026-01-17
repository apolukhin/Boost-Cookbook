if (!include(../../config.txt)) {
    error("Failed to open config.txt")
}

SOURCES += main.cpp
QMAKE_CXXFLAGS += $$CPP11FLAG

!msvc:LIBS += -lboost_thread $$BOOST_SYSTEM_LIBRARY -lboost_context
