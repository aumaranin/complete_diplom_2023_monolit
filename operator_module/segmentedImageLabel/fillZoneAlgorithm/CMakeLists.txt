cmake_minimum_required(VERSION 3.0.0)
project(fillZoneAlgorithm VERSION 0.1.0)

#find_package(GTest REQUIRED)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(
        fillZoneAlgorithm        
        SHARED
        fillZoneAlgorithm.h 
        fillZoneAlgorithm.cpp
    )

# include(CTest)
# enable_testing()

# add_executable(
#     fillZoneAlgorithm_test 
#         fillZoneAlgorithm_test.cpp
#         fillZoneAlgorithm.cpp
#         fillZoneAlgorithm.h
#     )

#     target_link_libraries(
#         ${PROJECT_NAME}_test 
#         PRIVATE GTest::gtest_main
#     )

#     enable_testing()
#     add_test(
#         NAME ${PROJECT_NAME}_test 
#         COMMAND $<TARGET_FILE:${PROJECT_NAME}_test>
#     )
