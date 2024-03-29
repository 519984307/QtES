# Target name
set(Target_Name utils)

# Header files
set(HDRS_FILES 
    utils_global.h
    environment.h
    fileutil.h
    hostosinfo.h
    runtimeerror.h
    singleton.hpp
    yamlutil.h
)

# Source files
set(SRCS_FILES 
    environment.cpp
    fileutil.cpp
    hostosinfo.cpp
    optional.hpp
    visit_struct.hpp
    yamlutil.cpp
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

add_definitions(-DUTILS_LIBRARY)

add_library(${Target_Name} SHARED 
    ${SRCS_FILES}
    ${HDRS_FILES} 
    ${UI_FILES} 
    ${MOC_SRCS}
    ${UI_HDRS} 
    ${RCS}
)
target_link_libraries(${Target_Name} ${QT_LIBRARIES} yaml-cpp log)
set_target_properties(${Target_Name} PROPERTIES VERSION 1.0.0 SOVERSION 1)

target_include_directories(${Target_Name} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../")

install(TARGETS ${Target_Name} 
        LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX})