include(../../global.prf)

Wizards_Name = Plugin-Wizards
Wizards_Dir = $$QMAKESPEC/../../../../Tools/QtCreator/share/qtcreator/templates/wizards/projects/$$Wizards_Name

TEMPLATE = subdirs

DISTFILES += \
    XXX.pro \
    XXXserviceimpl.cpp \
    XXXserviceimpl.h \
    XXXplugin.cpp \
    XXXplugin.h \
    XXXservice.h \
    XXX.json \
    lib.png \
    wizard.json \

message($(QTDIR))
message($$Wizards_Dir)

#copyFolder(, $$Wizards_Dir)

