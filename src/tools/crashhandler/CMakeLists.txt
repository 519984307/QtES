set(Target_Name crash_handler)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

# Header files
set(HDRS_FILES 
    backtracecollector.h
    crashhandlerdialog.h
    crashhandler.h
    utils.h
    ../../libs/utils/environment.h
)

# Source files
set(SRCS_FILES 
    main.cpp
    backtracecollector.cpp 
    crashhandlerdialog.cpp
    crashhandler.cpp
    utils.cpp
    ../../libs/utils/environment.cpp
)

# UI files
set(UI_FILES 
    crashhandlerdialog.ui
)

# Resources files
set(RCS_FILES 

)

# Headers that should run through moc
set(MOC_FILES 
  backtracecollector.h
  crashhandlerdialog.h
  crashhandler.h
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
target_link_libraries(${Target_Name} ${QT_LIBRARIES} widgets)

install(TARGETS ${Target_Name} RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX})
