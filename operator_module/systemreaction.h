#ifndef SYSTEMREACTION_H
#define SYSTEMREACTION_H

#include <string>
#include <vector>
using namespace std;

class SystemReaction
{
    int id;
    std::string type;
    string date;
    string confName;
    string zone;
    string classObject;
public:
    vector<string> missedProperties;
    SystemReaction();
    virtual std::string toJson() = 0;
    int getId() const;
    void setId(int newId);
    const std::string &getType() const;
    void setType(const std::string &newType);
    static SystemReaction *create(std::string json);
    virtual void execute() = 0;
    const string &getDate() const;
    void setDate(const string &newDate);
    const string &getConfName() const;
    void setConfName(const string &newConfName);
    const string &getZone() const;
    void setZone(const string &newZone);
    const string &getClassObject() const;
    void setClassObject(const string &newClassObject);
};

class NotifyOperator : public SystemReaction
{
public:
    NotifyOperator(){setType("NotifyOperator");}
    NotifyOperator(std::string json);
    virtual std::string toJson();
    virtual void execute();
};

class NoteToDatabase : public SystemReaction
{
public:
    NoteToDatabase(){setType("NoteToDatabase");}
    NoteToDatabase(std::string json);
    virtual std::string toJson();
    virtual void execute();
};

class SaveFrame : public SystemReaction
{
public:
    SaveFrame(){setType("SaveFrame");}
    SaveFrame(std::string json);
    virtual std::string toJson();
    virtual void execute();
};

class BashScript : public SystemReaction
{
    std::string fileName;


public:
    BashScript(){setType("BashScript");}
    BashScript(std::string json, bool flag);
    BashScript(std::string fileName) {setType("BashScript"); this->fileName = fileName;}
    const std::string &getFileName() const;
    void setFileName(const std::string &newFileName);
    virtual std::string toJson();
    virtual void execute();
};

#endif // SYSTEMREACTION_H
