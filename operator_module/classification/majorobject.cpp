#include "majorobject.h"

MajorObject::MajorObject()
{

}

string MajorObject::toJson()
{
    return "";
}

void MajorObject::displayObject(cv::Mat &frame, const cv::Scalar &color)
{
    for (auto minorObject : listMinorObject)
        minorObject->displayObject(frame, WHITE);
    //std::cout << "Мажорный объект. " << rect.x << ":" << rect.y << "  -  " << rect.x+rect.width << ":" << rect.y+rect.height << endl;
    cv::rectangle(frame, rect, color, 3);
}

void MajorObject::addProperty(shared_ptr<DetectObject> property)
{
    listMinorObject.push_back(property);
}

vector<int> MajorObject::getListSegments(int imgWidth, int imgHeight, int segSize)
{
    // Строим матрицу
    int n_rows;
    int n_cols;
    if (imgHeight%segSize)
        n_rows = imgHeight/segSize + 1;
    else
        n_rows = imgHeight/segSize;
    if (imgWidth%segSize)
        n_cols = imgWidth/segSize + 1;
    else
        n_cols = imgWidth/segSize;
    vector<vector<int>> matrix(n_rows);
    for (int i = 0; i < n_rows; ++i)
        matrix.at(i).resize(n_cols);


    // Вычисляем сегменты
    // top - это меньший индекс, чем верхний
    /*    *------------------>
     *    |
     *    |    1        3
     *    |
     *    |
     *    |    2        4
     *    |
     *    V
     *
     *    1 - left top
     *    2 - left bottom
     *    3 - right top
     *    4 - right bottom
     */

    int leftColumn = rect.x / segSize;
    int topRow = rect.y / segSize;
    int rightColumn = (rect.x + rect.width)/segSize;
    int bottomRow = (rect.y + rect.height)/segSize;

    for (int row = topRow; row < bottomRow; ++row)
        for (int column = leftColumn; column < rightColumn; ++column)
            matrix.at(row).at(column) = 1;

    for (int row = 0, i = 0; row<matrix.size(); ++row)
    {
        for (int column = 0; column < matrix.at(row).size(); ++column)
        {
            if (matrix.at(row).at(column))
                listSegments.push_back(i);
            ++i;
        }
    }

    return listSegments;
}

bool MajorObject::hasProperties(vector<string> ruleProps)
{
    vector<string> objProps;
    for (auto minorObj : listMinorObject)
        objProps.push_back(minorObj->toJson());
    for (auto rulepr : ruleProps)
    {
        bool flag = false;
        for (auto objpr : objProps)
        {
            if (rulepr == objpr)
            {
                flag = true;
                break;
            }
        }
        if (!flag)
            return false;
    }
    return true;
}

vector<string> MajorObject::getListProperties()
{
    vector<string> result;
    for (auto object : listMinorObject)
        result.push_back(object->toJson());
    return result;
}
