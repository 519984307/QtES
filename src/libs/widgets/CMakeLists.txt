# Target name
set(Target_Name widgets)

set(CMAKE_AUTOMOC ON)

file(GLOB HDRS_FILES
    "*.h"
    "frameless/*.h"
    "material/*.h"
    "material/lib/*.h"
)

file(GLOB SRCS_FILES
    "*.cpp"
    "frameless/*.cpp"
    "material/*.cpp"
    "material/lib/*.cpp"
)

file(GLOB UI_FILES
    "*.ui"
    "frameless/*.ui"
    "material/*.ui"
)

file(GLOB RCS_FILES
    "*.qrc"
    "frameless/*.qrc"
    "material/*.qrc"
)

# Headers that should run through moc
set(MOC_FILES 

)

# qt4_wrap_cpp(MOC_SRCS ${MOC_FILES})
qt4_wrap_ui(UI_HDRS ${UI_FILES})
qt4_add_resources(RCS ${RCS_FILES})

source_group("UI Files" FILES ${UI_FILES})
source_group("Generated Files" FILES ${MOC_SRCS} ${UI_HDRS})
source_group("Resources Files" FILES ${RCS})

add_definitions(-DWIDGETS_LIBRARY)

add_library(${Target_Name} STATIC 
    ${SRCS_FILES}
    ${HDRS_FILES} 
    ${UI_FILES} 
    # ${MOC_SRCS}
    ${UI_HDRS} 
    ${RCS}
)
target_link_libraries(${Target_Name} ${QT_LIBRARIES})
set_target_properties(${Target_Name} PROPERTIES VERSION 1.0.0 SOVERSION 1)

target_include_directories(${Target_Name} 
    PUBLIC 
        "${CMAKE_CURRENT_SOURCE_DIR}/../"
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/material
        # ${CMAKE_CURRENT_SOURCE_DIR}/material/lib
        # ${CMAKE_CURRENT_SOURCE_DIR}/material/layouts
)

INSTALL(TARGETS ${Target_Name} 
        LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX})
