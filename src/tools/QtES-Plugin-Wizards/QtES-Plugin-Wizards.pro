include(../../../global.pri)

Wizards_Name = QtES-Plugin-Wizards
#Wizards_Dir = $$QMAKESPEC/../../../../Tools/QtCreator/share/qtcreator/templates/wizards/projects/$$Wizards_Name

TEMPLATE = subdirs

DISTFILES += \
    CMakeLists.txt \
    XXX.pro \
    XXXserviceimpl.cpp \
    XXXserviceimpl.h \
    XXXplugin.cpp \
    XXXplugin.h \
    XXXservice.h \
    XXX.json \
    XXX.xml \
    lib.png \
    wizard.json \

#message($(QTDIR))
#message($$Wizards_Dir)

#copyFolder(, $$Wizards_Dir)
