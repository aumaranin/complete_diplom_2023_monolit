#ifndef CLASSIFICATIONALGORITHM_H
#define CLASSIFICATIONALGORITHM_H

#include "detectobject.h"
#include <opencv2/opencv.hpp>

class ClassificationAlgorithm
{
public:
    vector<string> allowedClasses;
    virtual vector<shared_ptr<DetectObject>> detect(cv::Mat &inputImage) = 0;
};

#endif

