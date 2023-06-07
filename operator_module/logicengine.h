#ifndef LOGICENGINE_H
#define LOGICENGINE_H

#include <QObject>
#include <QTimer>
#include <knowledgebase.h>
#include <memory>

class LogicEngine : QObject
{
    Q_OBJECT
    int timeDel;
public:
    shared_ptr<KnowledgeBase> knowledgeBase;
    LogicEngine() = delete;
    LogicEngine(int t);
    shared_ptr<QTimer> timer;
    int getTimeDel() const;
    void setTimeDel(int newTimeDel);

private slots:
    void timerAlert();
};

#endif // LOGICENGINE_H
