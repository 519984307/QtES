
set(Target_Name log)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/spdlog/include)

# Header files
set(HDRS_FILES 
    logger.h
    custome_file_sink.h
)

# Source files
set(SRCS_FILES 
    logger.cpp
)

add_library(${Target_Name} SHARED ${SRCS_FILES} ${HDRS_FILES})

target_link_libraries(${Target_Name} ${QT_LIBRARIES})
set_target_properties(${Target_Name} PROPERTIES VERSION 1.0.0 SOVERSION 1)

target_include_directories(${Target_Name} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../" "${CMAKE_CURRENT_SOURCE_DIR}/spdlog/include")

INSTALL(TARGETS ${Target_Name} 
        LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX})