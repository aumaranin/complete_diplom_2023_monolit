add_library(classificationmodule
    classificationalgorithm.h classificationalgorithm.cpp
    simpleyolo.h simpleyolo.cpp
    yolo2dnn.h yolo2dnn.cpp
    detectobject.cpp detectobject.h
    kbobject.cpp kbobject.h
    majorobject.cpp majorobject.h
    minoronject.cpp minoronject.h
    simpleyolov5.h simpleyolov5.cpp
    )

include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(classificationmodule ${OpenCV_LIBS} ${CMAKE_THREAD_LIBS_INIT})
