#ifndef MINORONJECT_H
#define MINORONJECT_H

#include "detectobject.h"

class MinorOnject : public DetectObject
{
public:
    MinorOnject();
    virtual string toJson() override;
    virtual void displayObject(cv::Mat &frame, const cv::Scalar &color) override;
    virtual void addProperty(shared_ptr<DetectObject> property) override;
    virtual bool hasProperties(vector<string> ruleProps) override;
    virtual vector<string> getListProperties() override;
};

#endif // MINORONJECT_H
