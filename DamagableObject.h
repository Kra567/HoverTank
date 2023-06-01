#ifndef DAMAGABLEOBJECT_H
#define DAMAGABLEOBJECT_H
#include <QPointF>
#include <QObject>
#include <map>
#include "abstractbody.h"
#include "polynomcurve.h"
#include "activity.h"
#include "body.h"

enum ObjectType{
    HERO,
    BARRIER,
    ENEMY,
    WALL,
    BULLET
};

using DamageMap = std::map<ObjectType,int>;


class DamagableObject : public Activity{
    Q_OBJECT
private:
    ObjectType type_;
    int health_;
    DamageMap damage_;
public:
    DamagableObject();
    DamagableObject(ObjectType type,int health,DamageMap damage);

    ObjectType getType();
    int typeDamage(ObjectType);
    void setHealth(int);
    void addHealth(int param);
    int getHealth();
    virtual QPointF getPosition() const = 0;
    virtual double getRadius() const = 0;
    virtual QPointF collisionCenter(const DamagableObject&) const = 0;
signals:
    void death();


    //virtual int wallDamage() = 0;

};


class BodyAssociated : public DamagableObject{
private:
    AbstractBody* body_;
public:
        BodyAssociated();
        BodyAssociated(AbstractBody*,ObjectType type,int health,DamageMap damage);
        QPointF getPosition() const override;
        double getRadius() const override;
        QPointF collisionCenter(const DamagableObject&) const override;
        AbstractBody* getBody();



};

class CurveAssociated : public DamagableObject{
private:
    PolynomCurve* curve_;
public:
    CurveAssociated();
    CurveAssociated(PolynomCurve*,ObjectType type,int health,DamageMap damage);
    QPointF getPosition() const override;
    double getRadius() const override;
    QPointF collisionCenter(const DamagableObject&) const override;
};




#endif // DAMAGABLEOBJECT_H
