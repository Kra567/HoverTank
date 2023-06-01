#include "platformbody.h"

PlatformBody::PlatformBody()
{

}

QPointF PlatformBody::getMapPos()
{
    double pos = Body::getPosition().x();
    //return platform_->getCurve()(pos) + Body::getRadius()*Platform::normalize(platform_->getTangent()(pos));
    return QPointF(0,0);
}

PlatformBody::PlatformBody(Platform *platform, double pos,double mass, double radius) : Body(QPointF(pos,0),mass,radius)
{
    platform_ = platform;
}


