#include "Source.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QString>

std::string IpCamera::getUrl(int type)
{
    //   rtsp://camera1:sasha_123@192.168.1.35:554/stream1
    std::string url;
    if (username.length()==0 || password.length()==0)
        //url = "rtsp://" + address + "/stream" + std::to_string(type);
        url = address;
    else
        url = "rtsp://" + username + ":" + password + "@" + address + "/stream" + std::to_string(type);
    return url;
}

Source * IpCamera::create(std::string name, std::string address, std::string username, std::string password)
{
    Source * newCamera = new IpCamera(name, address, username, password);
    newCamera->setType("IpCamera");
    return newCamera;
}

std::string IpCamera::toJson()
{
    using namespace std;
    string jsonRes;
    QJsonObject obj;
    obj["name"] = QString::fromStdString(getName());
    obj["type"] = QString::fromStdString(getType());
    obj["address"] = QString::fromStdString(address);
    obj["username"] = QString::fromStdString(username);
    obj["password"] = QString::fromStdString(password);
    QJsonDocument jout = QJsonDocument(obj);
    jsonRes = QString::fromUtf8(jout.toJson(QJsonDocument::JsonFormat::Compact)).toStdString();
    return jsonRes;
}

IpCamera::IpCamera(std::string jsonStr)
{
    using namespace std;
    QString qstr = QString::fromStdString(jsonStr);
    QJsonDocument jdoc = QJsonDocument::fromJson(qstr.toUtf8());
    QJsonObject obj = jdoc.object();
    setName(obj["name"].toString().toStdString());
    setType(obj["type"].toString().toStdString());
    address = obj["address"].toString().toStdString();
    username = obj["username"].toString().toStdString();
    password = obj["password"].toString().toStdString();
}

std::string UsbCamera::toJson()
{
    using namespace std;
    string jsonRes;
    QJsonObject obj;
    obj["name"] = QString::fromStdString(getName());
    obj["type"] = QString::fromStdString(getType());
    obj["device"] = QString::fromStdString(device);
    QJsonDocument jout = QJsonDocument(obj);
    jsonRes = QString::fromUtf8(jout.toJson(QJsonDocument::JsonFormat::Compact)).toStdString();
    return jsonRes;
}

UsbCamera::UsbCamera(std::string jsonStr)
{
    using namespace std;
    QString qstr = QString::fromStdString(jsonStr);
    QJsonDocument jdoc = QJsonDocument::fromJson(qstr.toUtf8());
    QJsonObject obj = jdoc.object();
    setName(obj["name"].toString().toStdString());
    setType(obj["type"].toString().toStdString());
    device = obj["device"].toString().toStdString();
}

std::string UsbCamera::getUrl(int type)
{
    std::string url = device;
    return url;
}

Source * UsbCamera::create(std::string name, std::string device)
{
    Source * newCamera = new UsbCamera(name, device);
    newCamera->setType("UsbCamera");
    return newCamera;
}

std::string VideoTape::getUrl(int type)
{
    return fileName;
}

Source *VideoTape::create(std::string name, std::string fileName)
{
    Source * newCamera = new VideoTape(name, fileName);
    newCamera->setType("VideoTape");
    return newCamera;
}

std::string VideoTape::toJson()
{
    using namespace std;
    string jsonRes;
    QJsonObject obj;
    obj["name"] = QString::fromStdString(getName());
    obj["type"] = QString::fromStdString(getType());
    obj["fileName"] = QString::fromStdString(fileName);
    QJsonDocument jout = QJsonDocument(obj);
    jsonRes = QString::fromUtf8(jout.toJson(QJsonDocument::JsonFormat::Compact)).toStdString();
    return jsonRes;
}

VideoTape::VideoTape(std::string jsonStr)
{
    using namespace std;
    QString qstr = QString::fromStdString(jsonStr);
    QJsonDocument jdoc = QJsonDocument::fromJson(qstr.toUtf8());
    QJsonObject obj = jdoc.object();
    setName(obj["name"].toString().toStdString());
    setType(obj["type"].toString().toStdString());
    fileName = obj["fileName"].toString().toStdString();
}

Source *Source::create(std::string json)
{
    using namespace std;
    Source *newSource;
    QString qstr = QString::fromStdString(json);
    QJsonDocument jdoc = QJsonDocument::fromJson(qstr.toUtf8());
    QJsonObject obj = jdoc.object();
    std::string type = obj["type"].toString().toStdString();
    if (type == "IpCamera")
    {
        newSource = new IpCamera(json);
    }
    else if (type == "UsbCamera")
    {
        newSource = new UsbCamera(json);
    }
    else if (type == "VideoTape")
    {
        newSource = new VideoTape(json);
    }
    return newSource;
}
