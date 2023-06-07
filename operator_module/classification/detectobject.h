#ifndef DETECTOBJECT_H
#define DETECTOBJECT_H

#include <string>
#include <vector>
#include <memory>
#include "kbobject.h"
#include <opencv2/opencv.hpp>

const cv::Scalar BLACK = cv::Scalar(0,0,0);
const cv::Scalar BLUE = cv::Scalar(255, 178, 50);
const cv::Scalar YELLOW = cv::Scalar(0, 255, 255);
const cv::Scalar RED = cv::Scalar(0,0,255);
const cv::Scalar WHITE = cv::Scalar(255,255,255);


using namespace std;

class DetectObject : public KBObject
{
public:
    DetectObject();

    string className;
    int imageHeight;
    int imageWidth;
    int segSize;
    cv::Rect rect;
    const string &getClassName() const;
    void setClassName(const string &newClassName);

    vector<int> listSegments;
    virtual vector<int> getListSegments(int imgWidth, int imgHeight, int segSize);
    void setListSegments(const vector<int> &newListSegments);

    virtual void displayObject(cv::Mat &frame, const cv::Scalar &color) = 0;
    virtual string toJson() override;
    virtual void addProperty(shared_ptr<DetectObject> property) = 0;
    virtual bool hasProperties(vector<string> ruleProps) = 0;
    virtual vector<string> getListProperties() = 0;
};

#endif // DETECTOBJECT_H
