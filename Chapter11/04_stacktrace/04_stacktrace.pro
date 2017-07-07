if (!include(../../config.txt)) {
    error("Failed to open config.txt")
}

SOURCES += main.cpp

#DEFINES += BOOST_STACKTRACE_USE_BACKTRACE=1

unix {
    !msvc:LIBS += -ldl -lbacktrace
}
