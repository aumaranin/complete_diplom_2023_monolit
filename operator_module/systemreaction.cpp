#include "systemreaction.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QString>
#include <QApplication>
#include "reportfromdb.h"
#include "global.h"


int SystemReaction::getId() const
{
    return id;
}

void SystemReaction::setId(int newId)
{
    id = newId;
}

const std::string &SystemReaction::getType() const
{
    return type;
}

void SystemReaction::setType(const std::string &newType)
{
    type = newType;
}

SystemReaction *SystemReaction::create(std::string json)
{
    using namespace std;
    SystemReaction *newReaction;
    QString qstr = QString::fromStdString(json);
    QJsonDocument jdoc = QJsonDocument::fromJson(qstr.toUtf8());
    QJsonObject obj = jdoc.object();
    std::string type = obj["type"].toString().toStdString();
    if (type == "NotifyOperator")
    {
        newReaction = new NotifyOperator(json);
    }
    else if (type == "SaveFrame")
    {
        newReaction = new SaveFrame(json);
    }
    else if (type == "NoteToDatabase")
    {
        newReaction = new NoteToDatabase(json);
    }
    else if (type == "BashScript")
    {
        newReaction = new BashScript(json, "true");
    }
    return newReaction;
}

const string &SystemReaction::getDate() const
{
    return date;
}

void SystemReaction::setDate(const string &newDate)
{
    date = newDate;
}

const string &SystemReaction::getConfName() const
{
    return confName;
}

void SystemReaction::setConfName(const string &newConfName)
{
    confName = newConfName;
}

const string &SystemReaction::getZone() const
{
    return zone;
}

void SystemReaction::setZone(const string &newZone)
{
    zone = newZone;
}

const string &SystemReaction::getClassObject() const
{
    return classObject;
}

void SystemReaction::setClassObject(const string &newClassObject)
{
    classObject = newClassObject;
}

SystemReaction::SystemReaction()
{

}

/*
SystemReaction::SystemReaction(string date, string confName, string zone, string classObject)
{
    this->date = date;
    this->confName = confName;
    this->zone = zone;
    this->classObject = classObject;
}
*/

NotifyOperator::NotifyOperator(std::string json)
{
    using namespace std;
    QString qstr = QString::fromStdString(json);
    QJsonDocument jdoc = QJsonDocument::fromJson(qstr.toUtf8());
    QJsonObject obj = jdoc.object();
    setType(obj["type"].toString().toStdString());
}

std::string NotifyOperator::toJson()
{
    using namespace std;
    string jsonRes;
    QJsonObject obj;
    obj["type"] = QString::fromStdString(getType());
    QJsonDocument jout = QJsonDocument(obj);
    jsonRes = QString::fromUtf8(jout.toJson(QJsonDocument::JsonFormat::Compact)).toStdString();
    return jsonRes;
}

std::string BashScript::toJson()
{
    using namespace std;
    string jsonRes;
    QJsonObject obj;
    obj["type"] = QString::fromStdString(getType());
    obj["fileName"] = QString::fromStdString(getFileName());
    QJsonDocument jout = QJsonDocument(obj);
    jsonRes = QString::fromUtf8(jout.toJson(QJsonDocument::JsonFormat::Compact)).toStdString();
    return jsonRes;
}

void BashScript::execute()
{
    std::string request = "bash " + fileName;
    system(request.c_str());
}

BashScript::BashScript(std::string json, bool flag)
{
    using namespace std;
    QString qstr = QString::fromStdString(json);
    QJsonDocument jdoc = QJsonDocument::fromJson(qstr.toUtf8());
    QJsonObject obj = jdoc.object();
    setType(obj["type"].toString().toStdString());
    fileName = obj["type"].toString().toStdString();
}

const std::string &BashScript::getFileName() const
{
    return fileName;
}

void BashScript::setFileName(const std::string &newFileName)
{
    fileName = newFileName;
}

SaveFrame::SaveFrame(std::string json)
{
    using namespace std;
    QString qstr = QString::fromStdString(json);
    QJsonDocument jdoc = QJsonDocument::fromJson(qstr.toUtf8());
    QJsonObject obj = jdoc.object();
    setType(obj["type"].toString().toStdString());
}

std::string SaveFrame::toJson()
{
    using namespace std;
    string jsonRes;
    QJsonObject obj;
    obj["type"] = QString::fromStdString(getType());
    QJsonDocument jout = QJsonDocument(obj);
    jsonRes = QString::fromUtf8(jout.toJson(QJsonDocument::JsonFormat::Compact)).toStdString();
    return jsonRes;
}



NoteToDatabase::NoteToDatabase(std::string json)
{
    using namespace std;
    QString qstr = QString::fromStdString(json);
    QJsonDocument jdoc = QJsonDocument::fromJson(qstr.toUtf8());
    QJsonObject obj = jdoc.object();
    setType(obj["type"].toString().toStdString());
}

std::string NoteToDatabase::toJson()
{
    using namespace std;
    string jsonRes;
    QJsonObject obj;
    obj["type"] = QString::fromStdString(getType());
    QJsonDocument jout = QJsonDocument(obj);
    jsonRes = QString::fromUtf8(jout.toJson(QJsonDocument::JsonFormat::Compact)).toStdString();
    return jsonRes;
}

void NoteToDatabase::execute()
{
    ReportFromDb report;
    report.setDate(this->getDate());
    report.setConfigName(this->getConfName());
    report.setZone(this->getZone());
    report.setClassObject(this->getClassObject());
    string reason = "Отсутствуют: ";
    for (auto item : missedProperties)
        reason = reason + " " + item;
    report.reason = reason;
    Global::getInstance().getDataBase()->writeReport(report);
}

void NotifyOperator::execute()
{

}

void SaveFrame::execute()
{

}
