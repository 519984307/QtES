include(../qtlockedfile/qtlockedfile.pri)

QT *= network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

HEADERS += \
    $$PWD/qtsingleapplication.h \
    $$PWD/qtlocalpeer.h

SOURCES += \
    $$PWD/qtsingleapplication.cpp \
    $$PWD/qtlocalpeer.cpp

