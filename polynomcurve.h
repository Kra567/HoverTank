#ifndef POLYNOMCURVE_H
#define POLYNOMCURVE_H
#include "polynomial.h"
#include <QPointF>
#include <QPainter>
#include "activity.h"

class PolynomCurve : public Activity
{
private:
    std::vector<QPointF> points_;
    //Polynomial polynom_x_;
    //Polynomial polynom_y_;
    //double begin_;
    //double end_;
public:
    PolynomCurve();
    PolynomCurve(const std::vector<QPointF>&);
    PolynomCurve(const PolynomCurve&);
    //Polynomial getXPolynom() const;
    //Polynomial getYPolynom() const;
    //double getBegin() const;
    //double getEnd() const;
    PolynomCurve& operator=(const PolynomCurve & curve){
        points_ = curve.points_;
        //polynom_x_ = curve.getXPolynom();
        //polynom_y_ = curve.getYPolynom();
        //begin_ = curve.getBegin();
        //end_ = curve.getEnd();
        return *this;
    };
    //static PolynomCurve Bezier(const std::vector<QPointF>&);
    //PolynomCurve(const Polynomial&,const Polynomial&,double begin,double end);
    void paint(QPainter&);
    //QPointF operator()(double) const;
    //std::optional<double> nearestTangent(const QPointF &) const;
    std::optional<QPointF> nearestTangent(const QPointF &);
    bool intersects(const QPointF& begin,const QPointF& end) const;
    static double dot(const QPointF&,const QPointF&);
    static std::optional<QPointF> projectPoint(const QPointF& begin,const QPointF& end,const QPointF& pos);
    static double snorm(const QPointF&);
    static double radianAngle(const QPointF&);
    void paintWithImage(QPainter&,const QImage&);




};

#endif // POLYNOMCURVE_H
