add_subdirectory(extensionsystem)
add_subdirectory(utils)
add_subdirectory(log)
add_subdirectory(widgets)


# # Target name
# set(Target_Name utils)

# file(GLOB_RECURSE HDRS_FILES *.h *.hpp)
# file(GLOB_RECURSE SRCS_FILES *.cpp *.cc *.cxx)
# file(GLOB_RECURSE UI_FILES *.ui)
# file(GLOB_RECURSE RCS_FILES *.qrc)

# qt4_wrap_cpp(MOC_SRCS ${HDRS_FILES})
# qt4_wrap_ui(UI_HDRS ${UI_FILES})
# qt4_add_resources(RCS ${RCS_FILES})

# source_group("UI Files" FILES ${UI_FILES})
# source_group("Generated Files" FILES ${MOC_SRCS} ${UI_HDRS})
# source_group("Resources Files" FILES ${RCS})

# add_library(${Target_Name} SHARED 
#     ${SRCS_FILES}
#     ${HDRS_FILES} 
#     ${UI_FILES} 
#     ${MOC_SRCS}
#     ${UI_HDRS} 
#     ${RCS}
# )
# target_link_libraries(${Target_Name} ${QT_LIBRARIES})
# set_target_properties(${Target_Name} PROPERTIES VERSION 1.0.0 SOVERSION 1)
# target_include_directories(${Target_Name} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
