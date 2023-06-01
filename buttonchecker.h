#ifndef BUTTONCHECKER_H
#define BUTTONCHECKER_H
#include <QObject>


class ButtonChecker : public QObject
{
    Q_OBJECT
public:
    ButtonChecker();
    void checkEvent();
signals:
    void left_arrow(bool);
    void right_arrow(bool);
    void up_arrow(bool);
    void down_arrow(bool);
};

#endif // BUTTONCHECKER_H
