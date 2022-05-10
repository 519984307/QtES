TEMPLATE = subdirs
CONFIG  += ordered

SUBDIRS += \
    QtES-Plugin-Wizards \

OTHER_FILES += \
    CMakeLists.txt \

linux-* {
    SUBDIRS += qtcreatorcrashhandler
}

