set(Target_Name shared_qtsingleapplication)

# Headers that should run through moc
set(MOC_FILES 
    qtsingleapplication.h
    qtlocalpeer.h
)
qt4_wrap_cpp(MOC_SRCS ${MOC_FILES})


add_library(${Target_Name} STATIC
    qtsinglecoreapplication.cpp 
    qtsinglecoreapplication.h
    qtsingleapplication.cpp 
    qtsingleapplication.h
    qtlocalpeer.cpp 
    qtlocalpeer.h  
    ${MOC_SRCS}
)
target_link_libraries(${Target_Name} shared_qtlockedfile Qt4::QtCore Qt4::QtNetwork)

target_include_directories(${Target_Name} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

if (WIN32)
  target_compile_definitions(${Target_Name} PRIVATE "QT_QTSINGLEAPPLICATION_EXPORT=__declspec(dllexport)")
endif()

