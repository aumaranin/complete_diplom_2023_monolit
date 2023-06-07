#include "minoronject.h"

MinorOnject::MinorOnject()
{

}

string MinorOnject::toJson()
{
    return className;
}

void MinorOnject::displayObject(cv::Mat &frame, const cv::Scalar &color)
{
    //std::cout << "Минорный объект. " << rect.x << ":" << rect.y << "  -  " << rect.x+rect.width << ":" << rect.y+rect.height << endl;
    cv::rectangle(frame, this->rect, color, 3);
}

void MinorOnject::addProperty(shared_ptr<DetectObject> property)
{

}

bool MinorOnject::hasProperties(vector<string> ruleProps)
{
    return true;
}

vector<string> MinorOnject::getListProperties()
{

}
