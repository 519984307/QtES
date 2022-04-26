include(../qtlockedfile/qtlockedfile.pri)


QT *= network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

HEADERS += \
    $$PWD/qtsinglecoreapplication.h \
    $$PWD/qtlocalpeer.h

SOURCES += \
    $$PWD/qtsinglecoreapplication.cpp \
    $$PWD/qtlocalpeer.cpp

