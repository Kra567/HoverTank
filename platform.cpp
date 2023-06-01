#include "platform.h"

Platform::Platform()
{
    curve_ = PolynomCurve();
    looped_ = 1;
    tangent_side_ = 1;
}

std::optional<double> Platform::touches(double rad, const QPointF &p )
{
    /*
    //std::optional<double> maybe_touch = curve_.nearestTangent(p);
    if (!maybe_touch.has_value()){
        return std::nullopt;
    }
    if (rad*rad >= PolynomCurve::snorm(p - curve_(maybe_touch.value()))){
        return std::make_optional(maybe_touch.value());
    }
    else{
        return std::nullopt;
    }
    */
    return std::nullopt;

}

PolynomCurve Platform::getCurve()
{
    return curve_;
}

PolynomCurve Platform::getTangent()
{
    /*
    if (tangent_side_){
        return PolynomCurve(curve_.getYPolynom().derivative(),(-1)*curve_.getXPolynom().derivative(),curve_.getEnd(),curve_.getBegin());
    }
    else{
        return PolynomCurve((-1)*curve_.getYPolynom().derivative(),curve_.getXPolynom().derivative(),curve_.getEnd(),curve_.getBegin());
    }
    */
    return PolynomCurve();
}

QPointF Platform::normalize(const QPointF &p)
{
    if (p == QPointF(0,0)){
        return p;
    }
    //qDebug() << "Snorm" << PolynomCurve::snorm(p);
    //qDebug() << "Normalize" << sqrt(PolynomCurve::snorm(p));
    return p/sqrt(PolynomCurve::snorm(p));
}

Platform::Platform(const PolynomCurve &curve, bool looped, bool tangent_side)
{
    curve_ = curve;
    looped_ = looped;
    tangent_side_ = tangent_side;
}
