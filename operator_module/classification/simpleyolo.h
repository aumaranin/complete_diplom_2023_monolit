#ifndef SIMPLEYOLO_H
#define SIMPLEYOLO_H

#include "classificationalgorithm.h"

class SimpleYolo : public ClassificationAlgorithm
{
public:
    vector<string> classNames;
    cv::dnn::Net net;
    SimpleYolo();
    virtual vector<shared_ptr<DetectObject>> detect(cv::Mat &inputImage) override;
    vector<cv::Mat> pre_process(cv::Mat &input_image);
    cv::Mat post_process(cv::Mat &input_image, vector<cv::Mat> &outputs);
};

#endif