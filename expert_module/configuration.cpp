#include "configuration.h"
#include "global.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QString>
#include "Source.h"

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
    periodComparison = 100;
}

Configuration::Configuration(std::string json)
{
    using namespace std;
    QString qstr = QString::fromStdString(json);
    QJsonDocument jdoc = QJsonDocument::fromJson(qstr.toUtf8());
    QJsonObject obj = jdoc.object();
    id = obj["id"].toInt();
    name = obj["name"].toString().toStdString();
    setSource(Source::create(obj["source"].toString().toStdString()));
    QJsonArray qRuleArray = obj["listRule"].toArray();
    for (const QJsonValue &item : qRuleArray)
    {
        Rule *rule = new Rule(item.toString().toStdString());
        listRule.push_back(rule);
        listZone.push_back(rule->getZone());
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
    for (Zone* zone : listZone)
        zoneArray.append(QString::fromStdString(zone->toJson()));
    obj["listZone"] = zoneArray;
    QJsonArray ruleArray;
    for (Rule* rule : listRule)
        ruleArray.append(QString::fromStdString(rule->toJson()));
    obj["listRule"] = ruleArray;
    QJsonDocument jout = QJsonDocument(obj);
    jsonRes = QString::fromUtf8(jout.toJson(QJsonDocument::JsonFormat::Compact)).toStdString();
    return jsonRes;
}
