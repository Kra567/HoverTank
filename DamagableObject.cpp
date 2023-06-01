#include "DamagableObject.h"


DamagableObject::DamagableObject()
{
    health_ = 0;
    damage_ = {};
    type_ = WALL;
}

DamagableObject::DamagableObject(ObjectType type, int health, DamageMap damage)
{

    type_ = type;
    health_ = health;
    damage_ = damage;
}

ObjectType DamagableObject::getType()
{
    return type_;
}

int DamagableObject::typeDamage(ObjectType type)
{
    if (damage_.count(type) == 0){
        return 0;
    }
    return damage_[type];
}

void DamagableObject::setHealth(int health)
{
    health_ = health;
    if (health_ <= 0){
        emit death();
        emit disactivate();
    }
    //qDebug() << this << " " << health_;
}

void DamagableObject::addHealth(int param)
{
    setHealth(getHealth() + param);
}

int DamagableObject::getHealth()
{
    return health_;
}

BodyAssociated::BodyAssociated(AbstractBody * body, ObjectType type, int health, DamageMap damage) : DamagableObject(type,health,damage)
{
    body_ = body;
    QObject::connect(this,SIGNAL(death()),body,SLOT(disactivate()));
    QObject::connect(body_,&Activity::disactivated,this,&Activity::disactivate);



}

QPointF BodyAssociated::getPosition() const
{
    return body_->getPosition();
}

double BodyAssociated::getRadius() const
{
    return body_->getRadius();
}

QPointF BodyAssociated::collisionCenter(const DamagableObject &) const
{
    return body_->getPosition();
}

AbstractBody *BodyAssociated::getBody()
{
    return body_;
}



CurveAssociated::CurveAssociated(PolynomCurve * curve, ObjectType type, int health, DamageMap damage) : DamagableObject(type,health,damage)
{
    curve_ = curve;
    QObject::connect(this,&DamagableObject::death,curve,&PolynomCurve::disactivate );
    QObject::connect(curve_,&Activity::disactivated,this,&Activity::disactivate);


}

QPointF CurveAssociated::getPosition() const
{
    return QPoint(0,0);
}

double CurveAssociated::getRadius() const
{
    return 0;
}

QPointF CurveAssociated::collisionCenter(const DamagableObject & obj) const
{
    double radius = obj.getRadius();
    QPointF pos = obj.getPosition();
    std::optional<QPointF> param = curve_->nearestTangent(pos);
    if (!param.has_value()){
        return QPointF(radius*3,radius*3) + pos;
    }
    return param.value();
}
