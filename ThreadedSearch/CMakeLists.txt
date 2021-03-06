cmake_minimum_required(VERSION 3.14)

project(ThreadedSearch VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Quick Concurrent Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Quick Concurrent Sql)

set(SRC_DIR src)
set(HDR_DIR hdr)

set(PROJECT_SOURCES
        hdr/common/Constants.h
        hdr/common/Defines.h
        src/main.cpp
        hdr/controller/SearchEngine.h
        src/controller/SearchEngine.cpp
        hdr/services/SearchDaemon.h
        src/services/SearchDaemon.cpp
        qml.qrc
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(ThreadedSearch
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET ThreadedSearch APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(ThreadedSearch SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(ThreadedSearch
          ${PROJECT_SOURCES}
        )
    endif()
endif()

target_compile_definitions(ThreadedSearch
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(ThreadedSearch
  PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick Qt${QT_VERSION_MAJOR}::Sql Qt${QT_VERSION_MAJOR}::Concurrent)

set_target_properties(ThreadedSearch PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_import_qml_plugins(ThreadedSearch)
    qt_finalize_executable(ThreadedSearch)
    qt6_add_qml_module(ThreadedSearch
        PLUGIN_TARGET ThreadedSearch
        VERSION 0.1
        RESOURCE_PREFIX qrc:/
        QML_FILES
            qml/common/components/KLine.qml
            qml/common/components/KTextInput.qml
            qml/common/screens/KMainScreen.qml
            qml/main.qml
    )
endif()

target_include_directories(ThreadedSearch PRIVATE
    hdr/controller
    hdr/common
    hdr/services)


