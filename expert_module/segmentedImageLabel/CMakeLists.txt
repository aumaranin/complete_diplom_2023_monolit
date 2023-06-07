cmake_minimum_required(VERSION 3.0.0)
project(segmentedImageLabel VERSION 0.1.0)

add_library(
    ${PROJECT_NAME} SHARED
        segmentedimagelabel.h
        segmentedimagelabel.cpp
    )

add_subdirectory(fillZoneAlgorithm)
target_link_libraries(${PROJECT_NAME} PRIVATE fillZoneAlgorithm)
target_include_directories(${PROJECT_NAME} PUBLIC fillZoneAlgorithm)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
