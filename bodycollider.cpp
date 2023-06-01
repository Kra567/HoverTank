#include "bodycollider.h"
#include "polynomcurve.h"
#include <set>

BodyCollider::BodyCollider()
{

}

void BodyCollider::addBody(AbstractBody *body)
{
    bodies_.push_back(body);

}

bool BodyCollider::isCollide(AbstractBody * body0, AbstractBody *body1)
{
    double epsilon = 0.001;
    double sdistance = PolynomCurve::snorm(body0->getPosition() - body1->getPosition());
    double bound = (body0->getRadius() + body1->getRadius() + epsilon);
    return (sdistance <= bound * bound);
}

bool BodyCollider::isIntersect(AbstractBody * body0, AbstractBody * body1)
{
    double sradd  = (body0->getRadius() + body1->getRadius())/2;
    return (PolynomCurve::snorm(body0->getPosition() - body1 -> getPosition())) < sradd*sradd;
}


// fix with acceleration
void BodyCollider::resolveCollide(AbstractBody * body0, AbstractBody *body1, double dt)
{
    double m0 = body0->getMass();
    double m1 = body1->getMass();
    QPointF v0 = (2*m1*body1->getVelocity() + body0->getVelocity()*(m0-m1))/(m0+m1);
    QPointF v1 = (2*m0*body0->getVelocity() + body1->getVelocity()*(m1-m0))/(m0+m1);
    body0->setVelocity(v0);
    body1->setVelocity(v1);


}

std::vector<AbstractBody *> BodyCollider::getBodies()
{
    return bodies_;
}

void BodyCollider::collision(double dt)
{


    // filter intersect
    //std::set<int> indices;
    //std::vector<AbstractBody*> res;

    /*
    for (int j = 0;j < bodies_.size();j++){
        bool ng = 1;

        for (int i = 0; i < j;i++){
            if (isIntersect(bodies_[i],bodies_[j])){
                bodies_[j]->disactivate();
                break;
            }
        }
    }
    */


    //filterActive<AbstractBody>(bodies_); - TO FIX BULLET - HERO COLLISION

    // collide
    for (int i = 0;i < bodies_.size();i++){
        for (int j = i+1;j < bodies_.size();j++){
            if (isCollide(bodies_[i],bodies_[j])){
                resolveCollide(bodies_[i],bodies_[j],dt);
            }
        }
    }
    filterActive<AbstractBody>(bodies_);
}
