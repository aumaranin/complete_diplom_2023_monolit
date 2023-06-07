#ifndef RULE_H
#define RULE_H

#include "kbobject.h"
#include "zone.h"
#include <string>
#include "systemreaction.h"

class Rule : public KBObject
{
    Zone *zone = nullptr;
    std::string name;
    std::string majorClass;
    std::vector<std::string> listProperties;
    std::vector<SystemReaction *> listSystemReaction;
public:
    Rule();
    Rule(std::string json);
    Zone *getZone() const;
    void setZone(Zone *newZone);
    const std::string &getMajorClass() const;
    void setMajorClass(const std::string &newMajorClass);
    const std::vector<std::string> &getListProperties() const;
    void setListProperties(const std::vector<std::string> &newListProperties);
    const std::vector<SystemReaction *> &getListSystemReaction() const;
    void setListSystemReaction(const std::vector<SystemReaction *> &newListSystemReaction);

    virtual std::string toJson();
    const std::string &getName() const;
    void setName(const std::string &newName);
};

#endif // RULE_H
