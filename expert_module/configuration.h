#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <string>
#include <vector>
#include <DataBase.h>
#include <Source.h>
#include <zone.h>
#include <rule.h>

using namespace std;

class Configuration
{
    int id;
    string name;
    DataBase *database;
    Source *source;
    vector<Zone*> listZone;
    vector<Rule *> listRule;
    int periodComparison;

public:
    Configuration();
    Configuration(string json);

    int getId() {return id;}
    void setId(const int &id) {this->id = id;}
    string getName() {return name;}
    void setName(const string &name) {this->name = name;}
    void setSource(Source *source) {this->source = source;}
    Source *getSource() {return source;}
    void setListZone(vector<Zone*> listZone) {this->listZone = listZone;}
    vector<Zone*> getListZone() {return listZone;}
    void setListRule(vector<Rule *> listRule) {this->listRule = listRule;}
    vector<Rule *> getListRule() {return listRule;}

    std::string toJson();

    int getPeriodComparison() const;
    void setPeriodComparison(int newPeriodComparison);
};

#endif // CONFIGURATION_H
