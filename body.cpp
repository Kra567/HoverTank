#include "body.h"

Body::Body()
{
    pos_ = QPointF(0,0);
    mass_ = 0;
    radius_ = 0;
}

double Body::getRadius()
{
    return radius_;
}

double Body::getMass()
{
    return mass_;
}

QPointF Body::getVelocity()
{
    return vel_;
}

QPointF Body::getPosition()
{
    return pos_;
}

QPointF Body::getAcceleration()
{
    return acc_;
}

void Body::setAcceleration(const QPointF & acc)
{
    acc_ = acc;
}

void Body::addAcceleration(const QPointF & acc)
{
    acc_ += acc;
}

void Body::setVelocity(const QPointF & vel)
{
    vel_ = vel;
}

void Body::addVelocity(const QPointF & vel)
{
    vel_ += vel;
}

void Body::connectGameTimer(GameTimer * timer)
{
    QObject::connect(timer,&GameTimer::timeoutInterval,this,&Body::requestForce);
    QObject::connect(timer,&GameTimer::timeoutInterval,this,&Body::changeVelocity);
    QObject::connect(timer,&GameTimer::timeoutInterval,this,&Body::changePos);
}

void Body::connectForce(Force * force)
{
    QObject::connect(this,&Body::getBody,force,&Force::actBody);
}


Body::Body(const QPointF &pos, double mass,double radius)
{
    pos_ = pos;
    mass_ = mass;
    radius_ = radius;
}

void Body::changePos(double dt)
{
    pos_ += vel_*dt + (dt*dt/2.0) * acc_;
}

void Body::changeVelocity(double dt)
{
    vel_ += dt * acc_;
}

void Body::requestForce(double dt)
{
    getBody(this,dt);
}

