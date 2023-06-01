#ifndef FORCES_H
#define FORCES_H
#include <QObject>
#include "abstractbody.h"


//class Body{};

class Force : public QObject {
    Q_OBJECT
public slots:
    virtual void actBody(AbstractBody*,double dt) = 0;
};

class VoidForce : public Force{
    Q_OBJECT
public:
    VoidForce();
public slots:
    void actBody(AbstractBody*,double) override;
};

class GravityForce: public Force

    {
    Q_OBJECT
public:
    GravityForce();
public slots:
    void actBody(AbstractBody*,double) override;

};

class MomentForce : public Force{
    Q_OBJECT
private:
    bool active_;
    QPointF value_;
public:
    MomentForce(const QPointF&);
public slots:
    void actBody(AbstractBody*,double) override;
};

class StateForce : public Force{
    Q_OBJECT
private:
    bool active_ = 0;
    QPointF value_;
public:
    StateForce(const QPointF&);
public slots:
    void actBody(AbstractBody*,double) override;
    void makeActive();
};

class AirDrag : public Force{
    Q_OBJECT
public:
    AirDrag();
public slots:
    void actBody(AbstractBody*,double) override;
};

class PointBarrierForce: public Force{
    Q_OBJECT
private:
    QPointF pos_;
    double radius_;
public:
    PointBarrierForce(const QPointF&,double rad);
public slots:
    void actBody(AbstractBody*,double) override;

};


class FrictionForce: public Force{
    Q_OBJECT
public:
    FrictionForce();
public slots:
    void actBody(AbstractBody*,double) override;
};

class StableForce : public Force{
    Q_OBJECT
private:
    QPointF acc_ = QPointF(0,0);
public:
    StableForce();
    QPointF getAcceleration();
    void setAcceleration(const QPointF&);
    void actBody(AbstractBody*,double);
};


class LimitForce : public Force{
    Q_OBJECT
private:
    double limitspeed_;
    QPointF acc_;
    bool active_ = 0;
public:
    LimitForce(double speed,const QPointF& acc);
    void actBody(AbstractBody*,double);
    void activate();
    void disactivate();
};


/*
class Limiter : public Force{
private:
    double limitspeed_;
public:

};
*/







#endif // FORCES_H
