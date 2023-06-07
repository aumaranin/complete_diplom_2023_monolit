#ifndef SYSTEMREACTION_H
#define SYSTEMREACTION_H

#include <string>

class SystemReaction
{
    int id;
    std::string type;
public:
    SystemReaction();

    virtual std::string toJson() = 0;
    int getId() const;
    void setId(int newId);
    const std::string &getType() const;
    void setType(const std::string &newType);
    static SystemReaction *create(std::string json);
};

class NotifyOperator : public SystemReaction
{
public:
    NotifyOperator(){setType("NotifyOperator");}
    NotifyOperator(std::string json);
    virtual std::string toJson();
};

class NoteToDatabase : public SystemReaction
{
public:
    NoteToDatabase(){setType("NoteToDatabase");}
    NoteToDatabase(std::string json);
    virtual std::string toJson();
};

class SaveFrame : public SystemReaction
{
public:
    SaveFrame(){setType("SaveFrame");}
    SaveFrame(std::string json);
    virtual std::string toJson();
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
};

#endif // SYSTEMREACTION_H
