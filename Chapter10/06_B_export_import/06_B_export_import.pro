if (!include(../../config.txt)) {
    error("Failed to open config.txt")
}

# There is a line in parent project:
# 06_B_export_import.depends = 06_A_my_library
# that forces `06_A_my_library` project
# build before building this project.

SOURCES += main.cpp
HEADERS += ../06_A_my_library/my_library.hpp
DEFINES += MY_LIBRARY_LINK_DYNAMIC

msvc {
    QMAKE_LFLAGS += /LIBPATH:../06_A_my_library/release
    QMAKE_LFLAGS += /LIBPATH:../06_A_my_library/debug
    QMAKE_LFLAGS += /LIBPATH:release
    QMAKE_LFLAGS += /LIBPATH:debug
    QMAKE_LFLAGS += /LIBPATH:../../Chapter10/06_A_my_library/release
    QMAKE_LFLAGS += /LIBPATH:../../Chapter10/06_A_my_library/debug
    QMAKE_LFLAGS += /LIBPATH:Chapter10/06_A_my_library/release
    QMAKE_LFLAGS += /LIBPATH:Chapter10/06_A_my_library/debug
} else {
    LIBS += -L../06_A_my_library
    LIBS += -L../06_A_my_library/release
    LIBS += -L../06_A_my_library/debug
}

LIBS += -l06_A_my_library

# We compile-in the path to the library.
unix|macos {
    QMAKE_LFLAGS+=-Wl,-rpath=../06_A_my_library/
    QMAKE_LFLAGS+=-Wl,-rpath=Chapter10/06_A_my_library/
}
