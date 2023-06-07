#include "logicengine.h"
#include "global.h"

LogicEngine::LogicEngine(int t)
{
    timeDel = t;
    timer = make_shared<QTimer>();
    timer->setInterval(t);
    connect(timer.get(), SIGNAL(timeout()), this, SLOT(timerAlert()));
}

int LogicEngine::getTimeDel() const
{
    return timeDel;
}

void LogicEngine::setTimeDel(int newTimeDel)
{
    timeDel = newTimeDel;
    timer->setInterval(newTimeDel);
}

void LogicEngine::timerAlert()
{
    //Global::getInstance().mode = Mode::DETECTION_STOP;
    timer->stop();
    knowledgeBase->flagComparison = true;
    //std::cout << "Таймер сработал: " << timeDel/1000 << " секунд"  << std::endl;

}
