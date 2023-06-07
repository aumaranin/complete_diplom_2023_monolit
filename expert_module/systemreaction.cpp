#include "systemreaction.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QString>

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

SystemReaction::SystemReaction()
{

}

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
