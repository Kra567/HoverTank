#ifndef DAMAGECOLLIDER_H
#define DAMAGECOLLIDER_H
#include "activity.h"
#include "DamagableObject.h"
#include <QObject>

class DamageCollider : public QObject
{
    Q_OBJECT
private:
    std::vector<DamagableObject*> objects_;

public:

    DamageCollider();
    void addObject(DamagableObject*);
    std::vector<DamagableObject*> getObjects();
    static bool isCollide(DamagableObject*,DamagableObject*);
    static void resolveCollide(DamagableObject*,DamagableObject*);
public slots:
    void collision();

};

#endif // DAMAGECOLLIDER_H
