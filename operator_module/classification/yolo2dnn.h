#ifndef YOLO2DNN_H
#define YOLO2DNN_H

#include "classificationalgorithm.h"

class Yolo2Dnn : public ClassificationAlgorithm
{
public:
    vector<string> classNamesMajor;
    vector<string> classNamesMinor;
    cv::dnn::Net netMajor;
    cv::dnn::Net netMinor;
    Yolo2Dnn();
    virtual vector<shared_ptr<DetectObject>> detect(cv::Mat &inputImage) override;

    template<typename T>
    vector<shared_ptr<DetectObject>> detectDnn(cv::Mat &inputImage, vector<string> &clNames, cv::dnn::Net &model);

    vector<shared_ptr<DetectObject>> comparison(vector<shared_ptr<DetectObject>> &listMajorObjects, vector<shared_ptr<DetectObject>> &listMinorObjects);
    bool between(cv::Rect major, cv::Rect minor);
};

#endif

