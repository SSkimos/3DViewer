cmake_minimum_required(VERSION 3.5)

project(3DViewer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_library (
    HELLO_LIB
    NAMES libmodel.a model # what to look for
    HINTS "${CMAKE_SOURCE_DIR}" # where to look
    NO_DEFAULT_PATH # do not search system default paths
)
find_library (
  MATRIX_T
    NAMES libs21_matrix.a matrix # what to look for
    HINTS "${CMAKE_SOURCE_DIR}/model/matrix_t" # where to look
    NO_DEFAULT_PATH # do not search system default paths
)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS OpenGLWidgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
message(STATUS "HELLO_LIB: [${HELLO_LIB}]")
#if (NOT HELLO_LIB)
#  #message(SEND_ERROR "Did not find lib hello")
#endif


set(PROJECT_SOURCES
        view/myglwidget.cpp
        view/myglwidget.h
        view/window.cpp
        view/window.ui
        data/position.h
        view/window.h
        main.cpp
)


if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(3DViewer
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET 3DViewer APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(3DViewer SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(3DViewer
            ${PROJECT_SOURCES}
        )
    endif()
endif()


target_link_libraries(3DViewer PRIVATE ${MATRIX_T})
target_link_libraries(3DViewer PRIVATE ${HELLO_LIB})
target_link_libraries(3DViewer PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(3DViewer PRIVATE Qt6::OpenGLWidgets)

set_target_properties(3DViewer PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(3DViewer)
endif()
