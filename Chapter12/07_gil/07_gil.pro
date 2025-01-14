if (!include(../../config.txt)) {
    error("Failed to open config.txt")
}

SOURCES += main.cpp
QMAKE_CXXFLAGS += $$CPP14FLAG


# Those paths are used by CI scripts of the book. You shall not find those libraries by that path in default Boost archive.
# Just install libpng into your system and add correct include paths to the build script.
INCLUDEPATH += $$BOOST_PATH/libpng/build/native/include
INCLUDEPATH += $$BOOST_PATH/libpng-v142/build/native/include
INCLUDEPATH += $$BOOST_PATH/zlib/build/native/include
INCLUDEPATH += $$BOOST_PATH/zlib.v140.windesktop.msvcstl.dyn.rt-dyn/build/native/include
INCLUDEPATH += $$BOOST_PATH/zlib_static/build/native/include
msvc {
    QMAKE_LFLAGS += /LIBPATH:$$BOOST_PATH/libpng/build/native/lib/x64/v140/dynamic/Release/
    QMAKE_LFLAGS += /LIBPATH:$$BOOST_PATH/libpng-v142/build/native/lib/x64/v142/Release/
    QMAKE_LFLAGS += /LIBPATH:$$BOOST_PATH/zlib_static/build/native/lib/Win32/v142/Release/MultiThreaded
    LIBS += -llibpng16
} else {
    unix {
        LIBS += -lpng
    } else {
        LIBS += -llibpng16
        QMAKE_LFLAGS += -L$$BOOST_PATH/libpng/build/native/lib/Win32/v140/dynamic/Release/
    }
}
