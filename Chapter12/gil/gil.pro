if (!include(../../config.txt)) {
    error("Failed to open config.txt")
}

SOURCES += main.cpp
QMAKE_CXXFLAGS += $$CPP11FLAG
!msvc:LIBS += -lpng

# Those paths are used by CI scripts of the book. You shall not find those libraries by that path in default Boost archive.
# Just install libpng into your system and add correct include paths to the build script.
INCLUDEPATH += $$BOOST_PATH/libpng/build/native/include
msvc:QMAKE_LFLAGS += /LIBPATH:$$BOOST_PATH/libpng/build/native/lib/x64/v140/dynamic/Release/
msvc:LIBS += -lpng16
