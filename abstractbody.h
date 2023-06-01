#ifndef ABSTRACTBODY_H
#define ABSTRACTBODY_H
#include <QPointF>
#include <QObject>
#include "activity.h"

class AbstractBody : public Activity {
      Q_OBJECT
public:
    virtual double getMass() = 0;
    virtual QPointF getVelocity() = 0;
    virtual QPointF getPosition() = 0;
    virtual void setAcceleration(const QPointF&) = 0;
    virtual void addAcceleration(const QPointF&) = 0;
    virtual QPointF getAcceleration() = 0;
    virtual double getRadius() = 0;
    virtual void setVelocity(const QPointF&) = 0;
    virtual void addVelocity(const QPointF&) = 0;
};




#endif // ABSTRACTBODY_H
