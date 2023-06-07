#ifndef RULE_H
#define RULE_H

#include "kbobject.h"
#include "zone.h"
#include <string>
#include "systemreaction.h"
#include <memory>

using namespace std;

class Rule : public KBObject
{
    shared_ptr<Zone> zone;
    std::string name;
    std::string majorClass;
    std::vector<std::string> listProperties;
    std::vector<shared_ptr<SystemReaction>> listSystemReaction;
public:
    Rule();
    Rule(std::string json);




    virtual std::string toJson();    
    const shared_ptr<Zone> &getZone() const;
    void setZone(const shared_ptr<Zone> &newZone);
    const std::string &getMajorClass() const;
    void setMajorClass(const std::string &newMajorClass);
    const std::vector<std::string> &getListProperties() const;
    void setListProperties(const std::vector<std::string> &newListProperties);
    const std::vector<shared_ptr<SystemReaction> > &getListSystemReaction() const;
    void setListSystemReaction(const std::vector<shared_ptr<SystemReaction> > &newListSystemReaction);
    const std::string &getName() const;
    void setName(const std::string &newName);
};

#endif // RULE_H
