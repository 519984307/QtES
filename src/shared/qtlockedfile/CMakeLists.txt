set(Target_Name shared_qtlockedfile)

if (WIN32)
  set(OS_SOURCES qtlockedfile_win.cpp)
else()
  set(OS_SOURCES qtlockedfile_unix.cpp)
endif()

# Headers that should run through moc
set(MOC_FILES 

)
qt4_wrap_cpp(MOC_SRCS ${MOC_FILES})

add_library(${Target_Name} STATIC 
    ${OS_SOURCES} 
    qtlockedfile.cpp 
    qtlockedfile.h 
    ${MOC_SRCS}
)
target_link_libraries(${Target_Name} Qt4::QtCore)

target_include_directories(${Target_Name} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

if (WIN32)
  target_compile_definitions(${Target_Name} PRIVATE
      "QT_QTLOCKEDFILE_EXPORT=__declspec(dllexport)" _UNICODE UNICODE)
endif()
