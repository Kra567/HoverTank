#ifndef BODY_H
#define BODY_H
#include <QPointF>
#include <QObject>
#include "gametimer.h"
#include "abstractbody.h"
#include "forces.h"

class Body : public AbstractBody
{
    Q_OBJECT
    // recalculate pos -> recalculate velocity -> recalculate acceleration
private:
    QPointF pos_;
    QPointF vel_ = QPointF(0,0);
    QPointF acc_ = QPointF(0,0);
    double mass_;
    double radius_;
public:
    Body();
    double getRadius() override;
    double getMass() override;
    QPointF getVelocity() override;
    QPointF getPosition() override ;
    QPointF getAcceleration() override;
    void setAcceleration(const QPointF&) override;
    void addAcceleration(const QPointF&) override;
    void setVelocity(const QPointF&) override;
    void addVelocity(const QPointF&) override;
    void connectGameTimer(GameTimer*);
    void connectForce(Force*);

    Body(const QPointF& pos,double mass,double radius);
public slots:
    void changePos(double);
    void changeVelocity(double);
    void requestForce(double);
signals:
    void getBody(Body*,double);
};

#endif // BODY_H
