#include "damagecollider.h"

DamageCollider::DamageCollider()
{

}

void DamageCollider::addObject(DamagableObject * obj)
{
    objects_.push_back(obj);
}

std::vector<DamagableObject *> DamageCollider::getObjects()
{
    return objects_;
}

bool DamageCollider::isCollide(DamagableObject * obj0, DamagableObject * obj1)
{
    QPointF colPos0 = obj0->collisionCenter(*obj1);
    QPointF colPos1 = obj1->collisionCenter(*obj0);
    double epsilon = 0.001;
    double distance = epsilon + obj0->getRadius() + obj1->getRadius();
    return PolynomCurve::snorm(colPos0-colPos1) <= distance*distance;
}

void DamageCollider::resolveCollide(DamagableObject * obj0, DamagableObject * obj1)
{
    obj0->addHealth(-obj1->typeDamage(obj0->getType()));
    obj1->addHealth(-obj0->typeDamage(obj1->getType()));
}

void DamageCollider::collision()
{

    filterActive<DamagableObject>(objects_);
    for (int i = 0; i < objects_.size();i++){
        for (int j = i+1; j < objects_.size();j++){
            if (isCollide(objects_[i],objects_[j])){
                resolveCollide(objects_[i],objects_[j]);
            }
        }
    }
}
