#ifndef PLATFORM_H
#define PLATFORM_H
#include "polynomcurve.h"

class Platform
{
private:
    bool looped_;
    bool tangent_side_; // 0 - contrclockwise, 1 - clockwise
    PolynomCurve curve_;

public:
    Platform(const PolynomCurve& curve,bool looped,bool tangent_side);
    Platform();
    std::optional<double> touches(double rad,const QPointF&);
    PolynomCurve getCurve();
    PolynomCurve getTangent();
    static QPointF normalize(const QPointF&);

};

#endif // PLATFORM_H
