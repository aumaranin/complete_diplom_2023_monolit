cmake_minimum_required(VERSION 3.5)

project(expert_module VERSION 0.1 LANGUAGES CXX)

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
        configurationlistwindow.cpp configurationlistwindow.h configurationlistwindow.ui
        settingdatabasewindow.h settingdatabasewindow.cpp settingdatabasewindow.ui        
        configurationmenu.h configurationmenu.cpp configurationmenu.ui
        configurationname.h configurationname.cpp configurationname.ui
        newcamera2.h newcamera2.cpp newcamera2.ui
        drawningZoneWindow.h drawningZoneWindow.cpp drawningZoneWindow.ui
        setrulewindow.h setrulewindow.cpp setrulewindow.ui


        DataBase.h Database.cpp
        global.h global.cpp
        configuration.h configuration.cpp
        Source.h Source.cpp
        drawinglabel.h drawinglabel.cpp
        kbobject.h kbobject.cpp
        zone.h zone.cpp
        systemreaction.h systemreaction.cpp
        rule.h rule.cpp

)

add_executable(expert_module
    ${PROJECT_SOURCES}
    )


target_link_libraries(expert_module PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(expert_module PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(expert_module)
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


add_subdirectory(segmentedImageLabel)
target_include_directories(${PROJECT_NAME} PUBLIC segmentedImageLabel)
target_link_libraries(${PROJECT_NAME} PRIVATE segmentedImageLabel)
