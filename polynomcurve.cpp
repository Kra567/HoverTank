#include "polynomcurve.h"
#include <QPainterPath>

/*
PolynomCurve::PolynomCurve()
{
    polynom_x_ = Polynomial();
    polynom_y_ = Polynomial();
    begin_ = 0;
    end_ = 0;
}

PolynomCurve::PolynomCurve(const PolynomCurve & curve)
{
    polynom_x_ = curve.polynom_x_;
    polynom_y_ = curve.polynom_y_;
    begin_ = curve.begin_;
    end_ = curve.end_;
}

Polynomial PolynomCurve::getXPolynom() const
{
    return polynom_x_;
}

Polynomial PolynomCurve::getYPolynom() const
{
    return polynom_y_;
}

double PolynomCurve::getBegin() const
{
    return begin_;
}

double PolynomCurve::getEnd() const
{
    return end_;
}



PolynomCurve PolynomCurve::Bezier(const std::vector<QPointF> & points)
{
    if (points.size() == 1){
        return PolynomCurve(Polynomial({points[0].x()}),Polynomial({points[0].y()}),0,1);
    }
    else{
        //qDebug() << "S";
        PolynomCurve bez0 = Bezier(std::vector<QPointF>(points.begin(),points.end()-1));
        PolynomCurve bez1 = Bezier(std::vector<QPointF>(points.begin()+1,points.end()));
        Polynomial pol0 = Polynomial({1,-1});
        Polynomial pol1 = Polynomial({0,1});
        //return PolynomCurve();
        //qDebug() << "iter";
        //qDebug() << pol0;
        //qDebug() << pol1;
        //qDebug() << bez0.getXPolynom();


        return PolynomCurve(pol0*bez0.getXPolynom() + bez1.getXPolynom()*pol1,
                            pol0*bez0.getYPolynom() + pol1*bez1.getYPolynom(),0,1);

    }
}



PolynomCurve::PolynomCurve(const Polynomial &px, const Polynomial &py, double begin, double end)
{
    polynom_x_ = px;
    polynom_y_ = py;
    begin_ = begin;
    end_ = end;
}

std::optional<double> PolynomCurve::nearestTangent(const QPointF & point) const
{
    Polynomial poly = getXPolynom().derivative()*(Polynomial({point.x()})+(-1)*getXPolynom())+
                      getYPolynom().derivative()*(Polynomial({point.y()})+(-1)*getYPolynom());
    std::vector<double> filtred;
    for (auto root : poly.findRoots()){
        if (root <= std::max(begin_,end_) && root >= std::min(begin_,end_)){
            filtred.push_back(root);
        }
    }
    if (filtred.empty()){
        return std::nullopt;
    }
    auto cmp = [&](const double& a,const double& b){return snorm((*this)(a) - point) < snorm((*this)(b) - point); };
    double res = *std::min_element(filtred.begin(), filtred.end(), cmp);
    return std::make_optional(res);
}

*/


PolynomCurve::PolynomCurve()
{


}

PolynomCurve::PolynomCurve(const std::vector<QPointF> & points)
{
    points_ = points;
}

PolynomCurve::PolynomCurve(const PolynomCurve & curve)
{
    points_ = curve.points_;
}

void PolynomCurve::paint(QPainter & painter)
{
    painter.setBrush(Qt::red);
    painter.setPen(Qt::red);
    for (int i = 0;i < points_.size()-1;i++){
        painter.drawLine(points_[i],points_[i+1]);
    }
}

std::optional<QPointF> PolynomCurve::nearestTangent(const QPointF & pos)
{
    double sdist = INT_MAX;
    std::optional<QPointF> res_point = std::nullopt;
    for (int i = 0;i < points_.size()-1;i++){
        std::optional<QPointF> proj = projectPoint(points_[i],points_[i+1],pos);
        if (proj.has_value()){
            double new_sdist = snorm(pos - proj.value());
            if (new_sdist < sdist){
                res_point = proj;
                sdist = new_sdist;
            }
        }

    }
    return res_point;
}

bool PolynomCurve::intersects(const QPointF &begin, const QPointF &end) const
{
    for (int i = 0;i < points_.size()-1;i++){
        //QPointF* res;
        auto res = QLineF(points_[i],points_[i+1]).intersects(QLineF(begin,end));
        if (res == QLineF::BoundedIntersection){
            return true;
        }
    }
    return false;
}

double PolynomCurve::dot(const QPointF & p0, const QPointF & p1)
{
    return p0.x()*p1.x() + p0.y()*p1.y();
}

std::optional<QPointF> PolynomCurve::projectPoint(const QPointF &begin, const QPointF &end, const QPointF &pos)
{
    double t = dot(begin - end,begin - pos)/dot(end-begin,end-begin);
    if (t >= 0 && t <= 1){
        return std::make_optional(begin + t*(end-begin));
    }
    double sdist_beg = snorm(begin - pos);
    double sdist_end = snorm(end - pos);
    if (sdist_beg < sdist_end){
        return begin;
    }
    return end;
}

double PolynomCurve::snorm(const QPointF &p )
{
    return p.x()*p.x() + p.y()*p.y();
}

double PolynomCurve::radianAngle(const QPointF & p)
{
    return arg(std::complex<double>(p.x(),p.y()));
}

void PolynomCurve::paintWithImage(QPainter & painter, const QImage & img)
{
    QPainterPath path;
    path.moveTo(points_[0]);
    for (int i = 1;i < points_.size();i++){
        path.lineTo(points_[i]);
    }
    painter.setBrush(QBrush(img));
    painter.drawPath(path);
}

/*
void PolynomCurve::paint(QPainter & painter)
{
    double eps = 1/(double)100;
    //qDebug() << eps;
    //qDebug() << (end_-begin_) << (end_-begin_)/eps;
    int amt = (double)(end_-begin_)/(double)eps;
    //qDebug() << amt << begin_ << end_;
    for (int i = 0;i < amt;i++){
        painter.drawLine((*this)(begin_+i*eps),(*this)(begin_+(i+1)*eps));
    }
}

*/
/*
QPointF PolynomCurve::operator()(double t) const
{
    return QPointF(polynom_x_(t),polynom_y_(t));
}
*/
