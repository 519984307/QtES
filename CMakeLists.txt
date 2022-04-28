cmake_minimum_required(VERSION 2.8.12)

project(QtES)
set(PROJECT_LONGNAME "QtES")
set(PROJECT_VERSION "1.0.0")

# Set policies
set(CMAKE_PROJECT_INCLUDE_BEFORE "${CMAKE_CURRENT_SOURCE_DIR}/cmake/EnableCMP0048.cmake")

# Global CMake options
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# # Turn on automatic invocation of the MOC, UIC & RCC
# set(CMAKE_AUTOMOC ON)
# set(CMAKE_AUTORCC ON)
# set(CMAKE_AUTOUIC ON)

ADD_DEFINITIONS(${QT_DEFINITIONS})

# Default configuration values. These must be before the project command or
# they won't work in Windows.
# If no build type is specified, default to "Release"
if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING
      "None Debug Release RelWithDebInfo MinSizeRel"
      FORCE)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -O3")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -m64 -pthread")#-fPIC 

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/install)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/libs)

# Configure Qt
find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})

add_subdirectory(src)
add_subdirectory(test)