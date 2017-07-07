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
    08_reading_files \
    09_coroutines

03_C_dll_usage.depends = \
    03_A_plugin_hello \
    03_B_plugin_do_not

