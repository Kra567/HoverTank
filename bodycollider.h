#ifndef BODYCOLLIDER_H
#define BODYCOLLIDER_H
#include "abstractbody.h"
#include <vector>
#include <QObject>

class BodyCollider : public QObject
{
    Q_OBJECT
private:
    std::vector<AbstractBody*> bodies_;

public:
    BodyCollider();
    void addBody(AbstractBody*);
    static bool isCollide(AbstractBody*,AbstractBody*);
    static bool isIntersect(AbstractBody*,AbstractBody*);
    static void resolveCollide(AbstractBody*,AbstractBody*,double dt);
    std::vector<AbstractBody*> getBodies();

public slots:
    void collision(double dt);
};

#endif // BODYCOLLIDER_H
