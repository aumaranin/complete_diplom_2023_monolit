#ifndef SIMPLEYOLOV5_H
#define SIMPLEYOLOV5_H

#include "classificationalgorithm.h"

class SimpleYoloV5 : public ClassificationAlgorithm
{
public:
    vector<string> classNames;
    cv::dnn::Net net;
    SimpleYoloV5();
    virtual vector<shared_ptr<DetectObject>> detect(cv::Mat &inputImage) override;
    vector<cv::Mat> pre_process(cv::Mat &input_image);
    cv::Mat post_process(cv::Mat &input_image, vector<cv::Mat> &outputs);


};

#endif
