#include "curvecollider.h"

CurveCollider::CurveCollider()
{

}

void CurveCollider::addCurve(PolynomCurve* curve)
{
    curves_.push_back(curve);
}

void CurveCollider::setCurve(const PolynomCurve & curve)
{
    if (curves_.empty()){
        return;
    }
    *curves_.back() = curve;
}

void CurveCollider::addBody(AbstractBody * body)
{
    bodies_.push_back(body);
}

std::vector<PolynomCurve*> CurveCollider::getCurves()
{
    return curves_;
}

std::optional<QPointF> CurveCollider::isCollide(PolynomCurve* curve, AbstractBody *body)
{
    std::optional<QPointF> par = curve->nearestTangent(body->getPosition());
    if (!par.has_value()){
        return std::nullopt;
    }
    double epsilon = 0.001;
    QPointF pot = par.value();
    double sdistance = PolynomCurve::snorm(pot - body->getPosition());
    if (sdistance <= ((body->getRadius() + epsilon) * (body->getRadius() + epsilon))){
        return std::make_optional(pot);
    }
    else{
        return std::nullopt;
    }
}

void CurveCollider::resolveCollide(const QPointF & T, AbstractBody *body)
{
    QPointF a = body->getPosition() - T;
    QPointF v = body->getVelocity();
    body->setVelocity(v - 2*a*PolynomCurve::dot(a,v)/PolynomCurve::dot(a,a));
}

void CurveCollider::debugPaint(QPainter & painter)
{

    painter.setBrush(Qt::green);
    painter.setPen(Qt::green);
    for (auto body : bodies_){
        for (auto curve : curves_){
            std::optional<QPointF> res = curve->nearestTangent(body->getPosition());
            if (res.has_value()){
                painter.drawLine(res.value(),body->getPosition());
            }
        }
    }
}
/*
double CurveCollider::dot(const QPointF & p0, const QPointF &p1)
{
    return p0.x()*p1.x() + p0.y()*p1.y();
}
*/

void CurveCollider::collision()
{
    filterActive<PolynomCurve>(curves_);
    filterActive<AbstractBody>(bodies_);
    for (auto curve : curves_){
        for (auto body_ref : bodies_){
            std::optional<QPointF> point = isCollide(curve,body_ref);
            //qDebug() << point.has_value();
            if (point.has_value()){
                resolveCollide(point.value(),body_ref);
            }
        }
    }
}
