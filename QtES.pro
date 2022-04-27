TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS = \
    src \

OTHER_FILES += \
    global.pri \
    rpath.pri \
    README.md \
    .clang-format \
    .clang-tidy \
    .gitignore
