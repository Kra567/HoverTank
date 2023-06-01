#ifndef CURVECOLLIDER_H
#define CURVECOLLIDER_H
#include <QObject>
#include "abstractbody.h"
#include "polynomcurve.h"
#include <optional>


class CurveCollider : public QObject
{
    Q_OBJECT
private:
    std::vector<PolynomCurve*> curves_;
    std::vector<AbstractBody*> bodies_;
public:
    CurveCollider();
    void addCurve(PolynomCurve*);
    void setCurve(const PolynomCurve&);
    void addBody(AbstractBody*);
    std::vector<PolynomCurve*> getCurves();
    static std::optional<QPointF> isCollide(PolynomCurve* curve,AbstractBody* body);
    static void resolveCollide(const QPointF&,AbstractBody*);
    void debugPaint(QPainter&);
    //static double dot(const QPointF&,const QPointF&);
public slots:
    void collision();

};

#endif // CURVECOLLIDER_H
