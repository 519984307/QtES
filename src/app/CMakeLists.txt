set(Target_Name app)

# Header files
set(HDRS_FILES 
    ../tools/crashhandler/crashhandlersetup.h
    app_version.h
)

# Source files
set(SRCS_FILES 
    main.cpp
    ../tools/crashhandler/crashhandlersetup.cpp
)

# UI files
set(UI_FILES 

)

# Resources files
set(RCS_FILES 

)

# Headers that should run through moc
set(MOC_FILES 

)


qt4_wrap_cpp(MOC_SRCS ${MOC_FILES})
qt4_wrap_ui(UI_HDRS ${UI_FILES})
qt4_add_resources(RCS ${RCS_FILES})

source_group("UI Files" FILES ${UI_FILES})
source_group("Generated Files" FILES ${MOC_SRCS} ${UI_HDRS})
source_group("Resources Files" FILES ${RCS})

add_executable(${Target_Name} 
    ${SRCS_FILES}
    ${HDRS_FILES} 
    ${UI_FILES} 
    ${MOC_SRCS}
    ${UI_HDRS} 
    ${RCS}
)
target_link_libraries(${Target_Name} ${QT_LIBRARIES} shared_qtsingleapplication extensionsystem utils)

install(TARGETS ${Target_Name} RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX})