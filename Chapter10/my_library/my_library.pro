if (!include(../../config.txt)) {
    error("Failed to open config.txt")
}

# We are NOT building an executable
TEMPLATE -= app

# ... we are building a library
TEMPLATE = lib

# Sources and headers of that library
SOURCES += my_library.cpp
HEADERS += my_library.hpp

# Making a dynamic library
DEFINES += MY_LIBRARY_LINK_DYNAMIC

