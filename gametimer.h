#ifndef GAMETIMER_H
#define GAMETIMER_H
#include <QObject>
#include <QTimer>

class GameTimer : public QTimer
{
    Q_OBJECT
public:
    int ticks = 0;
    GameTimer(QObject* parent = nullptr);
public slots:
    void getTimeout();
    void addTick();
signals:
    void timeoutInterval(double);

};

#endif // GAMETIMER_H
