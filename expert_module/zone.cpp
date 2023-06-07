#include "zone.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QString>

const std::string &Zone::getName() const
{
    return name;
}

void Zone::setName(const std::string &newName)
{
    name = newName;
}

const std::string &Zone::getDescription() const
{
    return description;
}

void Zone::setDescription(const std::string &newDescription)
{
    description = newDescription;
}

const std::string &Zone::getColor() const
{
    return color;
}

void Zone::setColor(const std::string &newColor)
{
    color = newColor;
}

const std::vector<int> &Zone::getListSegments() const
{
    return listSegments;
}

void Zone::setListSegments(const std::vector<int> &newListSegments)
{
    listSegments = newListSegments;
}

int Zone::getSegSize() const
{
    return segSize;
}

void Zone::setSegSize(int newSegSize)
{
    segSize = newSegSize;
}

int Zone::getFrameWidth() const
{
    return frameWidth;
}

void Zone::setFrameWidth(int newFrameWidth)
{
    frameWidth = newFrameWidth;
}

int Zone::getFrameHeight() const
{
    return frameHeight;
}

void Zone::setFrameHeight(int newFrameHeight)
{
    frameHeight = newFrameHeight;
}

std::string Zone::toJson()
{
    using namespace std;
    string jsonRes;
    QJsonObject obj;
    obj["name"] = QString::fromStdString(name);
    obj["description"] = QString::fromStdString(description);
    obj["color"] = QString::fromStdString(color);
    QJsonArray segmentArray;
    for (int segment : listSegments)
        segmentArray.append(segment);
    obj["listSegments"] = segmentArray;
    obj["segSize"] = segSize;
    obj["frameWidth"] = frameWidth;
    obj["frameHeight"] = frameHeight;
    QJsonDocument jout = QJsonDocument(obj);
    jsonRes = QString::fromUtf8(jout.toJson(QJsonDocument::JsonFormat::Compact)).toStdString();
    return jsonRes;
}

Zone *Zone::fromJson(std::string jsonStr)
{
    using namespace std;
    QString qstr = QString::fromStdString(jsonStr);
    QJsonDocument jdoc = QJsonDocument::fromJson(qstr.toUtf8());
    QJsonObject obj = jdoc.object();
    Zone *newZone = new Zone();
    newZone->setName(obj["name"].toString().toStdString());
    newZone->setDescription(obj["description"].toString().toStdString());
    newZone->setColor(obj["color"].toString().toStdString());
    vector<int> segmentArray;
    QJsonArray qSegmentArray = obj["listSegments"].toArray();
    for (const QJsonValue &item : qSegmentArray)
        segmentArray.push_back(item.toInt());
    newZone->setListSegments(segmentArray);
    newZone->setSegSize(obj["segSize"].toInt());
    newZone->setFrameWidth(obj["frameWidth"].toInt());
    newZone->setFrameHeight(obj["frameHeight"].toInt());
    return newZone;
}

Zone::Zone()
{

}

Zone::Zone(std::string name, std::string description, std::string color, int segSize, int frameWidth, int frameHeight)
{
    this->name = name;
    this->description = description;
    this->color = color;
    this->segSize = segSize;
    this->frameHeight = frameHeight;
    this->frameWidth = frameWidth;
}

Zone::Zone(std::string jsonString)
{
    using namespace std;
    QString qstr = QString::fromStdString(jsonString);
    QJsonDocument jdoc = QJsonDocument::fromJson(qstr.toUtf8());
    QJsonObject obj = jdoc.object();
    name = (obj["name"].toString().toStdString());
    setDescription(obj["description"].toString().toStdString());
    setColor(obj["color"].toString().toStdString());
    vector<int> segmentArray;
    QJsonArray qSegmentArray = obj["listSegments"].toArray();
    for (const QJsonValue &item : qSegmentArray)
        segmentArray.push_back(item.toInt());
    setListSegments(segmentArray);
    setSegSize(obj["segSize"].toInt());
    setFrameWidth(obj["frameWidth"].toInt());
    setFrameHeight(obj["frameHeight"].toInt());
}
