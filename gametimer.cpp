#include "gametimer.h"


GameTimer::GameTimer(QObject *parent) : QTimer(parent)
{
    QObject::connect(this,&GameTimer::timeout,this,&GameTimer::getTimeout);
    QObject::connect(this,&GameTimer::timeout,this,&GameTimer::addTick);
}

void GameTimer::getTimeout()
{
    timeoutInterval((this->interval()+1)/1000.0); //(this->interval()+1)/1000.0); // /1000.0);
}

void GameTimer::addTick()
{
    ticks++;
}
