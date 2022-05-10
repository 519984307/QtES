include(../../../global.pri)

TARGET = crash_handler
DESTDIR = $$BIN_DIR

CONFIG -= app_bundle
TEMPLATE = app

INCLUDEPATH += $$LIB_SRC_DIR
message($$LIB_SRC_DIR)

SOURCES += \
    main.cpp \
    backtracecollector.cpp \
    crashhandlerdialog.cpp \
    crashhandler.cpp \
    utils.cpp \
    ../../libs/widgets/checkablemessagebox.cpp \
    ../../libs/utils/environment.cpp

HEADERS += \
    backtracecollector.h \
    crashhandlerdialog.h \
    crashhandler.h \
    utils.h \
    ../../libs/widgets/checkablemessagebox.h \
    ../../libs/utils/environment.h

FORMS += \
    crashhandlerdialog.ui

OTHER_FILES += \
    CMakeLists.txt \
