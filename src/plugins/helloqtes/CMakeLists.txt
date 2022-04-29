set(Target_Name HelloQtES)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

# Header files
set(HDRS_FILES 
    helloqtesservice.h
    helloqtesserviceimpl.h
    helloqtesplugin.h
)

# Source files
set(SRCS_FILES 
    helloqtesserviceimpl.cpp
    helloqtesplugin.cpp
)

# UI files
set(UI_FILES 

)

# Resources files
set(RCS_FILES 
    resource.qrc
    HelloQtES.xml
)

qt4_wrap_ui(UI_HDRS ${UI_FILES})
qt4_add_resources(RCS ${RCS_FILES})

source_group("UI Files" FILES ${UI_FILES})
source_group("Generated Files" FILES ${UI_HDRS})
source_group("Resources Files" FILES ${RCS})

set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin/plugins)
add_library(${Target_Name} SHARED 
    ${SRCS_FILES}
    ${HDRS_FILES} 
    ${UI_FILES} 
    ${UI_HDRS} 
    ${RCS}
)
target_link_libraries(${Target_Name} ${QT_LIBRARIES} extensionsystem)
set_target_properties(${Target_Name} PROPERTIES AUTOMOC TRUE)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/${Target_Name}.xml DESTINATION ${LIBRARY_OUTPUT_PATH})
INSTALL(TARGETS ${Target_Name} 
        LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/plugins)
INSTALL(FILES ${Target_Name}.xml
        DESTINATION ${CMAKE_INSTALL_PREFIX}/plugins)
