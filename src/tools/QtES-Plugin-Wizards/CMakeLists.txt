set(Target_Name %{ProjectName})

# Header files
set(HDRS_FILES
    %{ServiceHdrFileName}
    %{ServiceImplHdrFileName}
    %{PluginHdrFileName}
)

# Source files
set(SRCS_FILES
    %{ServiceImplSrcFileName}
    %{PluginSrcFileName}
)

# UI files
set(UI_FILES

)

# Resources files
set(RCS_FILES
    resource.qrc
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

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/%{ProjectName}.xml DESTINATION ${LIBRARY_OUTPUT_PATH})
install(TARGETS ${Target_Name}
        LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/plugins)
install(FILES ${Target_Name}.xml
        DESTINATION ${CMAKE_INSTALL_PREFIX}/plugins)
