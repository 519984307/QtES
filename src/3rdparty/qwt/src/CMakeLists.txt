cmake_minimum_required(VERSION 2.8.12)

set(Target_Name qwt)

project(${Target_Name})
set(PROJECT_VERSION "6.2.0")

include_directories(${CMAKE_CURRENT_BINARY_DIR})

file(GLOB SRCS
    "*.cpp"
)

find_package(Qt4 REQUIRED QtCore QtGui QtSvg QtXml QtOpenGL)
include(${QT_USE_FILE})

add_definitions(${QT_DEFINITIONS})

add_library(${Target_Name} ${SRCS})
target_link_libraries(${Target_Name} ${QT_LIBRARIES})

target_include_directories(${Target_Name} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
