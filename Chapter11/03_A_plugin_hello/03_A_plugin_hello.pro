if (!include(../../config.txt)) {
    error("Failed to open config.txt")
}

# We are NOT building an executable
TEMPLATE -= app

# ... we are building a library.
TEMPLATE = lib

# Sources and headers of the library.
SOURCES += plugin_hello.cpp
