#include "forces.h"
#include "abstractbody.h"
#include "polynomcurve.h"
#include "platform.h"

VoidForce::VoidForce(){

}

GravityForce::GravityForce(){

}

void VoidForce::actBody(AbstractBody* body,double dt){
    body->setAcceleration(QPointF(0,0));
}

void GravityForce::actBody(AbstractBody* body,double dt){
    body->addAcceleration(QPointF(0,50));
}

MomentForce::MomentForce(const QPointF& p)
{
    active_ = 1;
    value_ = p;
}

void MomentForce::actBody(AbstractBody * body, double)
{
    if (active_){
         body->addAcceleration(value_/body->getMass());
         active_ = 0;
    }

}

StateForce::StateForce(const QPointF & val)
{
    value_ = val;
}

void StateForce::actBody(AbstractBody * body, double)
{
    if (active_){
        body->addAcceleration(value_/body->getMass());
    }
    active_ = 0;
}

void StateForce::makeActive()
{
    active_ = 1;
}

AirDrag::AirDrag()
{

}

void AirDrag::actBody(AbstractBody * body, double)
{
    double coeff = 0.01;
    QPointF vel = body->getVelocity();
    body->addAcceleration(-coeff*sqrt(PolynomCurve::snorm(vel))*vel);
}

PointBarrierForce::PointBarrierForce(const QPointF & pos, double rad)
{
    pos_ = pos;
    radius_ = rad;
}

void PointBarrierForce::actBody(AbstractBody * body, double)
{
    if (PolynomCurve::snorm(body->getPosition() - pos_) == 0){
        qDebug() << "You suck";
    }
    //double dist_coeff = radius_ / sqrt(PolynomCurve::snorm(body->getPosition() - pos_));
    //double coeff = sqrt(PolynomCurve::snorm(body->getAcceleration()));
    QPointF way = Platform::normalize(body->getPosition() - pos_);
    if (PolynomCurve::snorm(body->getPosition()-pos_) <= radius_*radius_ ){
        //body->addAcceleration(coeff * way );
        //body->addAcceleration(PolynomCurve::snorm(body->getAcceleration())*way);
        body->addVelocity(sqrt(PolynomCurve::snorm(body->getVelocity()))*way);
    }
}

FrictionForce::FrictionForce()
{

}

void FrictionForce::actBody(AbstractBody * body, double)
{
    //if (body->getVelocity() != QPointF(0,0)){
    body->addAcceleration(-100*Platform::normalize(body->getVelocity()));
    //}
}

StableForce::StableForce()
{

}

QPointF StableForce::getAcceleration()
{
    return acc_;
}

void StableForce::setAcceleration(const QPointF &acc)
{
    acc_ = acc;
}

void StableForce::actBody(AbstractBody * body, double)
{
    body->addAcceleration(acc_);
}



LimitForce::LimitForce(double speed, const QPointF &acc)
{
    limitspeed_ = speed;
    acc_ = acc;
}

void LimitForce::actBody(AbstractBody *body, double)
{
    if (active_ && (PolynomCurve::snorm(body->getVelocity()) <= limitspeed_*limitspeed_ ) ){
        body->addAcceleration(acc_);
        //active_ = 0;
    }
}

void LimitForce::activate()
{
    active_ = 1;
}

void LimitForce::disactivate()
{
    active_ = 0;
}


