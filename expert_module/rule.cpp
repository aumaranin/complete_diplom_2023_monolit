#include "rule.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QString>

Zone *Rule::getZone() const
{
    return zone;
}

void Rule::setZone(Zone *newZone)
{
    zone = newZone;
}

const std::string &Rule::getMajorClass() const
{
    return majorClass;
}

void Rule::setMajorClass(const std::string &newMajorClass)
{
    majorClass = newMajorClass;
}

const std::vector<std::string> &Rule::getListProperties() const
{
    return listProperties;
}

void Rule::setListProperties(const std::vector<std::string> &newListProperties)
{
    listProperties = newListProperties;
}

const std::vector<SystemReaction *> &Rule::getListSystemReaction() const
{
    return listSystemReaction;
}

void Rule::setListSystemReaction(const std::vector<SystemReaction *> &newListSystemReaction)
{
    listSystemReaction = newListSystemReaction;
}

const std::string &Rule::getName() const
{
    return name;
}

void Rule::setName(const std::string &newName)
{
    name = newName;
}

Rule::Rule()
{

}

Rule::Rule(std::string json)
{
    using namespace std;
    QString qstr = QString::fromStdString(json);
    QJsonDocument jdoc = QJsonDocument::fromJson(qstr.toUtf8());
    QJsonObject obj = jdoc.object();
    name = obj["name"].toString().toStdString();
    majorClass = obj["majorClass"].toString().toStdString();
    QJsonArray qPropertiesArray = obj["listProperties"].toArray();
    for (const QJsonValue &item : qPropertiesArray)
        listProperties.push_back(item.toString().toStdString());
    QJsonArray qReactionArray = obj["listSystemReaction"].toArray();
    for (const QJsonValue &item : qReactionArray)
    {
        SystemReaction *reaction = SystemReaction::create(item.toString().toStdString());
        listSystemReaction.push_back(reaction);
    }
    zone = new Zone(obj["zone"].toString().toStdString());
}

std::string Rule::toJson()
{
    using namespace std;
    string jsonRes;
    QJsonObject obj;
    obj["name"] = QString::fromStdString(name);
    obj["majorClass"] = QString::fromStdString(majorClass);
    QJsonArray propertiesArray;
    for (std::string property : listProperties)
        propertiesArray.append(QString::fromStdString(property));
    obj["listProperties"] = propertiesArray;

    QJsonArray reactionArray;
    for (SystemReaction* reaction : listSystemReaction)
        reactionArray.append(QString::fromStdString(reaction->toJson()));
    obj["listSystemReaction"] = reactionArray;
    obj["zone"] = QString::fromStdString(zone->toJson());
    QJsonDocument jout = QJsonDocument(obj);
    jsonRes = QString::fromUtf8(jout.toJson(QJsonDocument::JsonFormat::Compact)).toStdString();

    return jsonRes;
}
