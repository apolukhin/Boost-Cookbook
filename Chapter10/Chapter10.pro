TEMPLATE = subdirs

SUBDIRS += \
    int128 \
    no_rtti \
    extern_template \
    constexpr_c++11 \
    noexcept_c++11 \
    export_import \
    my_library \
    version \

export_import.depends = my_library
