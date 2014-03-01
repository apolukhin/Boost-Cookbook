if (!include(../../config.txt)) {
    error("Failed to open config.txt")
}

SOURCES += main.cpp

# If unix like OS => link with 'rt' library
unix {
    LIBS += -lrt
}
