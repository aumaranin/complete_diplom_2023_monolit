#include "configuration.h"
#include "global.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QString>
#include "Source.h"

const vector<shared_ptr<Zone> > &Configuration::getListZone() const
{
    return listZone;
}

void Configuration::setListZone(const vector<shared_ptr<Zone> > &newListZone)
{
    listZone = newListZone;
}

const vector<shared_ptr<Rule> > &Configuration::getListRule() const
{
    return listRule;
}

void Configuration::setListRule(const vector<shared_ptr<Rule> > &newListRule)
{
    listRule = newListRule;
}

const shared_ptr<Source> &Configuration::getSource() const
{
    return source;
}

void Configuration::setSource(const shared_ptr<Source> &newSource)
{
    source = newSource;
}

int Configuration::getPeriodComparison() const
{
    return periodComparison;
}

void Configuration::setPeriodComparison(int newPeriodComparison)
{
    periodComparison = newPeriodComparison;
}

Configuration::Configuration()
{

}

Configuration::Configuration(std::string json)
{
    using namespace std;
    QString qstr = QString::fromStdString(json);
    QJsonDocument jdoc = QJsonDocument::fromJson(qstr.toUtf8());
    QJsonObject obj = jdoc.object();
    id = obj["id"].toInt();
    name = obj["name"].toString().toStdString();
    shared_ptr<Source> src(Source::create(obj["source"].toString().toStdString()));
    setSource(src);
    QJsonArray qRuleArray = obj["listRule"].toArray();
    for (const QJsonValue &item : qRuleArray)
    {
        shared_ptr<Rule> rule (new Rule(item.toString().toStdString()));
        shared_ptr<Zone> zone (rule->getZone());
        listRule.push_back(rule);
        listZone.push_back(zone);
    }
    periodComparison = obj["periodComparison"].toInt();
}

string Configuration::toJson()
{
    using namespace std;
    string jsonRes;
    QJsonObject obj;
    obj["id"] = id;
    obj["periodComparison"] = periodComparison;
    obj["name"] = QString::fromStdString(name);
    obj["source"] = QString::fromStdString(source->toJson());
    QJsonArray zoneArray;
    for (auto zone : listZone)
        zoneArray.append(QString::fromStdString(zone->toJson()));
    obj["listZone"] = zoneArray;
    QJsonArray ruleArray;
    for (auto rule : listRule)
        ruleArray.append(QString::fromStdString(rule->toJson()));
    obj["listRule"] = ruleArray;
    QJsonDocument jout = QJsonDocument(obj);
    jsonRes = QString::fromUtf8(jout.toJson(QJsonDocument::JsonFormat::Compact)).toStdString();
    return jsonRes;
}
