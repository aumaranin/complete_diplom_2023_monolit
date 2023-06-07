#ifndef MAJOROBJECT_H
#define MAJOROBJECT_H

#include "detectobject.h"

class MajorObject : public DetectObject
{
public:
    MajorObject();
    vector <shared_ptr<DetectObject>> listMinorObject;
    virtual string toJson() override;
    virtual void displayObject(cv::Mat &frame, const cv::Scalar &color) override;
    virtual void addProperty(shared_ptr<DetectObject> property) override;
    virtual vector<int> getListSegments(int imgWidth, int imgHeight, int segSize) override;
    virtual bool hasProperties(vector<string> ruleProps) override;
    virtual vector<string> getListProperties() override;
};

#endif // MAJOROBJECT_H
