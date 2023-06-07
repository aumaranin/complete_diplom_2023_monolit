#include "detectobject.h"

DetectObject::DetectObject()
{

}

const string &DetectObject::getClassName() const
{
    return className;
}

void DetectObject::setClassName(const string &newClassName)
{
    className = newClassName;
}

vector<int> DetectObject::getListSegments(int imgWidth, int imgHeight, int segSize)
{
    return listSegments;
}

void DetectObject::setListSegments(const vector<int> &newListSegments)
{
    listSegments = newListSegments;
}

string DetectObject::toJson()
{
    return "";
}
