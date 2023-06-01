#include "graphs.h"

GraphMap::GraphMap(){

}

std::vector<QPoint> GraphMap::potentiallyConnected(const QPoint & p)
{
    return                  {p + QPoint(interval_,0),
                p + QPoint(0,interval_),
                p + QPoint(interval_,interval_),
                p + QPoint(interval_,-interval_),
                p + QPoint(-interval_,0),
                p + QPoint(0,-interval_),
                p + QPoint(-interval_,-interval_),
                p + QPoint(-interval_,interval_)};
}

GraphMap::GraphMap(const QPoint& vert0,const QPoint& vert1,int interval){
    interval_ = interval;
    for (int xa = 0;xa <= (vert1.x() - vert0.x())/interval + 1;xa ++){
        for (int ya = 0;ya <= (vert1.y() - vert0.y())/interval + 1;ya++){
            QPoint p = vert0 + interval*(QPoint(xa,0) + QPoint(0,ya));
            graph_[p] = potentiallyConnected(p);
        }
    }
    begin_ = vert0;
    end_ = vert1;
    interval_ = interval;
}

QPoint GraphMap::findNearest(const QPointF & pos)
{
    QPoint p = begin_ + interval_*((pos.toPoint() - begin_)/interval_);
    if (!graph_.contains(p)){
        for (auto c : potentiallyConnected(p)){
            //qDebug() << graph_[c].size();
            if (graph_.contains(p)){
                qDebug() << "SUIIIII";
                return c;
            }
        }
    }
    return p;

}

std::vector<QPointF> GraphMap::getVectors(const QPointF& find,const std::vector<QPointF> & points)
{
    std::vector<QPoint> conv;
    for (auto p : points){
        conv.push_back(findNearest(p));
    }
    std::vector<QPoint> prevs = findPrevious(graph_,findNearest(find),conv);
    std::vector<QPointF> res;
    for (int i = 0;i < prevs.size();i++){
        res.push_back(prevs[i] - conv[i]);
    }
    return res;
}

void GraphMap::bakeMap(const PolynomCurve & curve)
{
    for (int xa = 0;xa <= (end_.x() - begin_.x())/interval_ + 1;xa ++){
        for (int ya = 0;ya <= (end_.y() - begin_.y())/interval_ + 1;ya++){
            QPoint p = begin_ + interval_*QPoint(xa,ya);
            for (auto c : potentiallyConnected(p)
                 ){
                if (curve.intersects(p,c)){
                    //qDebug() << "S";
                    dropEdge(graph_,p,c);
                }
            }
        }
    }
}

std::vector<QPoint> GraphMap::shortestWay(const QPointF & beg, const QPointF & end)
{
    QPoint p0 = findNearest(end);
    QPoint p1 = findNearest(beg);
    return shortestPath(graph_,p0,p1);
}

void GraphMap::paint(QPainter & painter)
{
    painter.setBrush(QColorConstants::Svg::purple);
    painter.setPen(QColorConstants::Svg::purple);
    for (auto key : graph_.keys()){
        for (auto con : graph_[key]){
            painter.drawLine(con,key);
        }
    }
}
