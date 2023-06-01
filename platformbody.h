#ifndef PLATFORMBODY_H
#define PLATFORMBODY_H
#include "body.h"
#include "platform.h"


class PlatformBody : public Body
{
private:
    Platform* platform_;
public:
    PlatformBody(Platform* platform,double pos,double mass,double radius);
    PlatformBody();
    QPointF getMapPos();
};

#endif // PLATFORMBODY_H
