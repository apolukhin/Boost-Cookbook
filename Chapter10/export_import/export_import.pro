if (!include(../../config.txt)) {
    error("Failed to open config.txt")
}

# There is a line in parent project:
# export_import.depends = my_library
# that forces `my_library` project
# build before building this project.

SOURCES += main.cpp
HEADERS += ../my_library/my_library.hpp
DEFINES += MY_LIBRARY_LINK_DYNAMIC
LIBS += -L../my_library -lmy_library
