#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <string>
#include <vector>
#include <DataBase.h>
#include <Source.h>
#include <zone.h>
#include <rule.h>
#include <memory>

using namespace std;

class Configuration
{
    int id;
    string name;
    shared_ptr<DataBase> database;
    shared_ptr<Source> source;
    vector<shared_ptr<Zone>> listZone;
    vector<shared_ptr<Rule>> listRule;
    int periodComparison;

public:
    Configuration();
    Configuration(string json);

    int getId() {return id;}
    void setId(const int &id) {this->id = id;}
    string getName() {return name;}
    void setName(const string &name) {this->name = name;}


    std::string toJson();

    const shared_ptr<Source> &getSource() const;
    void setSource(const shared_ptr<Source> &newSource);
    const vector<shared_ptr<Zone> > &getListZone() const;
    void setListZone(const vector<shared_ptr<Zone> > &newListZone);
    const vector<shared_ptr<Rule> > &getListRule() const;
    void setListRule(const vector<shared_ptr<Rule> > &newListRule);
    int getPeriodComparison() const;
    void setPeriodComparison(int newPeriodComparison);
};

#endif // CONFIGURATION_H
