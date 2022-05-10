set(Target_Name extensionsystem)

# Header files
set(HDRS_FILES 
    aggregate.h
    plugindetailsview.h
    invoker.h
    iplugin.h
    iplugin_p.h
    extensionsystem_global.h
    pluginmanager.h
    pluginmanager_p.h
    pluginspec.h
    pluginspec_p.h
    pluginview.h
    optionsparser.h
    plugincollection.h
    pluginerroroverview.h
    pluginerrorview.h
)

# Source files
set(SRCS_FILES 
    aggregate.cpp
    pluginerrorview.cpp
    plugindetailsview.cpp
    invoker.cpp
    iplugin.cpp
    pluginmanager.cpp
    pluginspec.cpp
    pluginview.cpp
    optionsparser.cpp
    plugincollection.cpp
    pluginerroroverview.cpp
)

# UI files
set(UI_FILES 
    pluginview.ui
    pluginerrorview.ui
    plugindetailsview.ui
    pluginerroroverview.ui
)

# Resources files
set(RCS_FILES 
    pluginview.qrc
)

# Headers that should run through moc
set(MOC_FILES 
    aggregate.h
    plugindetailsview.h
    iplugin.h
    pluginmanager.h
    pluginmanager_p.h
    pluginspec_p.h
    pluginview.h
    pluginerroroverview.h
    pluginerrorview.h
)

qt4_wrap_cpp(MOC_SRCS ${MOC_FILES})
qt4_wrap_ui(UI_HDRS ${UI_FILES})
qt4_add_resources(RCS ${RCS_FILES})

source_group("UI Files" FILES ${UI_FILES})
source_group("Generated Files" FILES ${MOC_SRCS} ${UI_HDRS})
source_group("Resources Files" FILES ${RCS})

add_definitions(-DEXTENSIONSYSTEM_LIBRARY)

add_library(${Target_Name} SHARED 
    ${SRCS_FILES}
    ${HDRS_FILES} 
    ${UI_FILES} 
    ${MOC_SRCS}
    ${UI_HDRS} 
    ${RCS}
)
target_link_libraries(${Target_Name} ${QT_LIBRARIES})
set_target_properties(${Target_Name} PROPERTIES VERSION 1.0.0 SOVERSION 1)

target_include_directories(${Target_Name} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../")

INSTALL(TARGETS ${Target_Name} 
        LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX})
