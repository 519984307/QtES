cmake_minimum_required(VERSION 2.8.12)

set(Target_Name qwt)

project(${Target_Name})
set(PROJECT_VERSION "6.2.0")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
# set(CMAKE_AUTOMOC ON)
find_package(Qt4 REQUIRED QtCore QtGui QtSvg QtXml QtOpenGL)
include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})

include_directories(${CMAKE_CURRENT_BINARY_DIR})

file(GLOB SRCS_FILES
    "*.cpp"
)

file(GLOB HDRS_FILES
    "*.h"
)

# Headers that should run through moc
set(MOC_FILES 
    qwt_abstract_legend.h
    qwt_abstract_scale.h
    qwt_abstract_slider.h
    qwt_analog_clock.h
    qwt_compass.h
    qwt_counter.h
    qwt_dial.h
    qwt_dyngrid_layout.h
    qwt_knob.h
    qwt_legend_label.h
    qwt_legend.h
    qwt_magnifier.h
    qwt_panner.h
    qwt_picker.h
    qwt_plot_canvas.h
    qwt_plot_glcanvas.h
    qwt_plot_magnifier.h
    qwt_plot_panner.h
    qwt_plot_picker.h
    qwt_plot_renderer.h
    qwt_plot_rescaler.h
    qwt_plot_zoomer.h
    qwt_plot.h
    qwt_polar_canvas.h
    qwt_polar_magnifier.h
    qwt_polar_panner.h
    qwt_polar_picker.h
    qwt_polar_plot.h
    qwt_polar_renderer.h
    qwt_sampling_thread.h
    qwt_scale_widget.h
    qwt_slider.h
    qwt_text_label.h
    qwt_thermo.h
    qwt_wheel.h
    qwt_widget_overlay.h
)

qt4_wrap_cpp(MOC_SRCS ${MOC_FILES})

add_library(${Target_Name} STATIC 
    ${SRCS_FILES} 
    ${HDRS_FILES}
    ${MOC_SRCS}
)
target_link_libraries(${Target_Name} ${QT_LIBRARIES})

target_include_directories(${Target_Name} PUBLIC 
    "${CMAKE_CURRENT_SOURCE_DIR}" 
    "${CMAKE_CURRENT_SOURCE_DIR}/../classincludes"
)
