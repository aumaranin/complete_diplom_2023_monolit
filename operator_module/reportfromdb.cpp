#include "reportfromdb.h"

const string &ReportFromDb::getDate() const
{
    return date;
}

void ReportFromDb::setDate(const string &newDate)
{
    date = newDate;
}

const string &ReportFromDb::getConfigName() const
{
    return configName;
}

void ReportFromDb::setConfigName(const string &newConfigName)
{
    configName = newConfigName;
}

const string &ReportFromDb::getZone() const
{
    return zone;
}

void ReportFromDb::setZone(const string &newZone)
{
    zone = newZone;
}

const string &ReportFromDb::getClassObject() const
{
    return classObject;
}

void ReportFromDb::setClassObject(const string &newClassObject)
{
    classObject = newClassObject;
}

ReportFromDb::ReportFromDb()
{

}

const string &ReportFromDb::getReason() const
{
    return reason;
}

void ReportFromDb::setReason(const string &newReason)
{
    reason = newReason;
}
