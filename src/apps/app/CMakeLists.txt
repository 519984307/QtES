set(Target_Name app)

add_definitions(-DENABLE_LOG)

EXEC_PROGRAM(
    "git"
    ${CMAKE_CURRENT_SOURCE_DIR}
    ARGS " --git-dir=${PROJECT_SOURCE_DIR}/.git --work-tree=${PROJECT_SOURCE_DIR} log -1 | head -n 1"
    OUTPUT_VARIABLE BUILD_COMMIT_
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

EXEC_PROGRAM(
    "git"
    ${CMAKE_CURRENT_SOURCE_DIR}
    ARGS " --git-dir=${PROJECT_SOURCE_DIR}/.git --work-tree=${PROJECT_SOURCE_DIR} rev-parse --abbrev-ref HEAD"
    OUTPUT_VARIABLE BUILD_BRANCH_
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

EXEC_PROGRAM(
    "git"
    ${CMAKE_CURRENT_SOURCE_DIR}
    ARGS " --git-dir=${PROJECT_SOURCE_DIR}/.git --work-tree=${PROJECT_SOURCE_DIR} tag -l | tail -n 1"
    OUTPUT_VARIABLE BUILD_TAG_
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

EXEC_PROGRAM(
    "date"
    ${CMAKE_CURRENT_SOURCE_DIR}
    ARGS " +%F"
    OUTPUT_VARIABLE BUILD_DATE_
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

EXEC_PROGRAM(
    "date"
    ${CMAKE_CURRENT_SOURCE_DIR}
    ARGS " +%T"
    OUTPUT_VARIABLE BUILD_TIME_
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

SET(VERSION_MAJOR_ 0)
SET(VERSION_MINOR_ 0)
SET(VERSION_REVISION_ 1)
SET(VERSION_FULL_ ${VERSION_MAJOR_}.${VERSION_MINOR_}.${VERSION_REVISION_})

CONFIGURE_FILE(
    ${CMAKE_CURRENT_LIST_DIR}/version_info.in.h
    ${CMAKE_CURRENT_LIST_DIR}/version_info.h
)

# Header files
set(HDRS_FILES 
    ../../tools/crashhandler/crashhandlersetup.h
    ../version_ini_tag.h
    ${CMAKE_CURRENT_LIST_DIR}/version_info.h
)

# Source files
set(SRCS_FILES 
    main.cpp
    ../../tools/crashhandler/crashhandlersetup.cpp
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
target_link_libraries(${Target_Name} ${QT_LIBRARIES} log shared_qtsingleapplication extensionsystem utils)

install(TARGETS ${Target_Name} RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX})
