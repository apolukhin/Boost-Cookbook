if (!include(../../config.txt)) {
    error("Failed to open config.txt")
}

SOURCES += main.cpp
DEFINES += BOOST_ALL_NO_LIB=1
QMAKE_CXXFLAGS += $$CPP11FLAG

!msvc:LIBS += -lboost_thread -lboost_system -lboost_context
