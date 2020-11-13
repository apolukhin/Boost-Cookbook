TEMPLATE = subdirs

SUBDIRS += \
    01_listing_files \
    02_erasing_files \
    03_A_plugin_hello \
    03_B_plugin_do_not \
    03_C_dll_usage \
    04_stacktrace \
    05_interprocess_basics \
    06_interprocess_queue \
    07_interprocess_pointers \
    08_reading_files

# Some strange link errors on come MinGW implementations:
#
#   Cannot export _jump_fcontext: symbol not found
#   Cannot export _make_fcontext: symbol not found
#   Cannot export _ontop_fcontext: symbol not found
#   collect2.exe: error: ld returned 1 exit status
!win32-g++ {
    SUBDIRS += 09_coroutines
}


03_C_dll_usage.depends = \
    03_A_plugin_hello \
    03_B_plugin_do_not

