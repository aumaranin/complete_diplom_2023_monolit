#ifndef REPORTFROMDB_H
#define REPORTFROMDB_H

#include <string>

using namespace std;

class ReportFromDb
{
    string date;
    string configName;
    string zone;
    string classObject;

public:
    ReportFromDb();
    string reason;
    const string &getDate() const;
    void setDate(const string &newDate);
    const string &getConfigName() const;
    void setConfigName(const string &newConfigName);
    const string &getZone() const;
    void setZone(const string &newZone);
    const string &getClassObject() const;
    void setClassObject(const string &newClassObject);
    const string &getReason() const;
    void setReason(const string &newReason);
};

#endif // REPORTFROMDB_H
