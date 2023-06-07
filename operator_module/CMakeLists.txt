cmake_minimum_required(VERSION 3.5)

project(operator_module VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        operatorstackedwindow.cpp operatorstackedwindow.h operatorstackedwindow.ui
        configuration.cpp configuration.h
        Database.cpp DataBase.h
        kbobject.cpp kbobject.h
        rule.cpp rule.h
        Source.cpp Source.h
        systemreaction.cpp systemreaction.h
        zone.cpp zone.h
        global.h global.cpp
        qvideolabel.h qvideolabel.cpp
        #qcheckconfiguration.h qcheckconfiguration.cpp
        knowledgebase.h knowledgebase.cpp
        videoengine.h videoengine.cpp
        qdetectionlabel.h qdetectionlabel.cpp
        qtablelabel.h qtablelabel.cpp
        #qtablewidgetitemdoubleclick.h qtablewidgetitemdoubleclick.cpp
        logicengine.h logicengine.cpp
        reportfromdb.h reportfromdb.cpp
        logwindow.h logwindow.cpp logwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(operator_module
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET operator_module APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(operator_module SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(operator_module
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(operator_module PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(operator_module PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(operator_module)
endif()


find_package(libmongocxx REQUIRED)
find_package(libbsoncxx REQUIRED)
include_directories(${LIBMONGOCXX_INCLUDE_DIR})
include_directories(${LIBBSONCXX_INCLUDE_DIR})
include_directories("/usr/local/include/mongocxx/v_noabi")
include_directories("/usr/local/include/bsoncxx/v_noabi")
include_directories("/usr/local/include/libmongoc-1.0")
include_directories("/usr/local/include/libbson-1.0")
include_directories("/usr/local/lib")
target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBMONGOCXX_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBBSONCXX_LIBRARIES})

# Подключение сервисной библиотеки с дополнительными функциями к основной программе
add_subdirectory(serviceFunctions)
target_include_directories(${PROJECT_NAME} PRIVATE serviceFunctions)
target_link_libraries(${PROJECT_NAME} PRIVATE serviceFunctions)

# Подключение OpenCV библиотек к основной программе
find_package( OpenCV REQUIRED )
#target_include_directories(${PROJECT_NAME} PRIVATE ${OpenCV_INCLUDE_DIRS} )
include_directories( ${OpenCV_INCLUDE_DIRS} )
target_link_libraries(${PROJECT_NAME} PRIVATE ${OpenCV_LIBS})

add_subdirectory(classification)
target_include_directories(${PROJECT_NAME} PUBLIC classificationmodule)
target_link_libraries(${PROJECT_NAME} PRIVATE classificationmodule)
