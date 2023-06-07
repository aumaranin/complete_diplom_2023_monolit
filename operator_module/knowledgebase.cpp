#include "knowledgebase.h"
#include <QString>
#include <QDateTime>

KnowledgeBase::KnowledgeBase()
{

}

void KnowledgeBase::compare()
{
    bool flagComparison = false;
    for (auto &rule : listRule)
        for (auto &object : listObjects)
        {
            // Сравнение основных классов
            if (rule->getMajorClass() == object->className)
            {
                for (auto &ruleZoneSegment : rule->getZone()->getListSegments())
                    for (auto &objectSegment : object->getListSegments(rule->getZone()->getFrameWidth(), rule->getZone()->getFrameHeight(), rule->getZone()->getSegSize()))
                        if (ruleZoneSegment == objectSegment)
                        {
                            vector<string> listMissed = getMissed(rule->getListProperties(), object->getListProperties());
                            // Сравнение свойств
                            if (listMissed.size())
                            {
                                cout << "Обнаружено нарушение ТБ" << endl;
                                executeReaction(rule, listMissed);
                                return;
                            }
                        }
            }
        }
}

void KnowledgeBase::executeReaction(shared_ptr<Rule> rule, vector<string> missedProperties)
{
    QString format = "yyyy.MM.dd  HH::mm:ss";
    QDateTime current = QDateTime::currentDateTime();
    std::string date = current.toString(format).toStdString();
    for (auto &reaction : rule->getListSystemReaction())
    {
        reaction->setClassObject(rule->getMajorClass());
        reaction->setZone(rule->getZone()->getName());
        reaction->setConfName(configurationName);
        reaction->setDate(date);
        reaction->missedProperties = missedProperties;
        reaction->execute();
    }
}

vector<string> KnowledgeBase::getMissed(vector<string> ruleProperties, vector<string> objectProperties)
{
    cout << "Свойства правила: ";
    for (auto property : ruleProperties)
        cout << property << " ";
    cout << endl;

    cout << "Свойства объекта: ";
    for (auto property : objectProperties)
        cout << property << " ";
    cout << endl;

    vector<string> missed;
    for (auto ruleProperty : ruleProperties)
    {
        bool flag = false;
        for (auto objectProperty : objectProperties)
            if (QString::fromStdString(ruleProperty).trimmed() == QString::fromStdString(objectProperty).trimmed())
            {
                flag = true;
                break;
            }
        if (!flag)
            missed.push_back(ruleProperty);
    }

    cout << "Отсутствует: ";
    for (auto item : missed)
        cout << item << " ";
    cout << endl;
    return missed;
}
