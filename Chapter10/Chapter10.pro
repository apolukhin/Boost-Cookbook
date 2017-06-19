TEMPLATE = subdirs

SUBDIRS += \
    01_predef \
    02_int128 \
    03_no_rtti \
    04_constexpr_c++11 \
    05_noexcept_c++11 \
    06_A_my_library \
    06_B_export_import \
    07_version

06_B_export_import.depends = 06_A_my_library
