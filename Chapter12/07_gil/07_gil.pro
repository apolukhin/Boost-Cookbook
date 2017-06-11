if (!include(../../config.txt)) {
    error("Failed to open config.txt")
}

SOURCES += main.cpp
QMAKE_CXXFLAGS += $$CPP11FLAG


# Those paths are used by CI scripts of the book. You shall not find those libraries by that path in default Boost archive.
# Just install libpng into your system and add correct include paths to the build script.
INCLUDEPATH += $$BOOST_PATH/libpng/build/native/include
msvc {
    QMAKE_LFLAGS += /LIBPATH:$$BOOST_PATH/libpng/build/native/lib/x64/v140/dynamic/Release/
    LIBS += -llibpng16
} else {
    unix {
        LIBS += -lpng
    } else {
        LIBS += -llibpng16
        QMAKE_LFLAGS += -L$$BOOST_PATH/libpng/build/native/lib/Win32/v140/dynamic/Release/
    }
}
