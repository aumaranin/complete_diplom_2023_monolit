#ifndef KNOWLEDGEBASE_H
#define KNOWLEDGEBASE_H

#include <string>
#include <vector>
#include <memory>
#include "zone.h"
#include "rule.h"
#include <classification/detectobject.h>

using namespace std;

class KnowledgeBase
{
public:
    KnowledgeBase();
    bool flagComparison;
    vector<shared_ptr<Zone>> listZone;
    vector<shared_ptr<Rule>> listRule;
    vector<shared_ptr<DetectObject>> listObjects;
    void compare();
    void executeReaction(shared_ptr<Rule> rule, vector<string> missedProperties);
    string configurationName;

    vector<string> getMissed(vector<string> ruleProperties, vector<string> objectProperties);
};

#endif // KNOWLEDGEBASE_H
