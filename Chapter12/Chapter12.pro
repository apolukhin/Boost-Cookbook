TEMPLATE = subdirs

SUBDIRS += \
    graph \
    graph_vis \
    random \
    math \
    testing \
    testing_advanced

!msvc:SUBDIRS += gil

