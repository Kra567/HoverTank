#ifndef GRAPHS_H
#define GRAPHS_H
#include <QHash>
#include <QQueue>
#include "polynomcurve.h"
#include <QPainter>
#include <set>

template<typename T>
using Graph = QHash<T,std::vector<T>>;

template<typename T>
std::vector<T> shortestPath(const Graph<T>& graph,const T& begin,const T& end){
    if (end == begin){
        return {};
    }
    QQueue<T> que;
    QHash<T,bool> checked;
    QHash<T,T> prev;
    checked[begin] = 0;
    que.enqueue(begin);
    while (!que.isEmpty()){
        T vert = que.dequeue();
        for (auto con : graph[vert]){
            if (!checked.contains(con)){
                que.enqueue(con);
                checked[con] = 0;
                prev[con] = vert;
            }
            else{
            }
        }
    }
    //qDebug() << "EndZer";


    std::vector<T> res;
    T curr = end;
    while (curr != begin){
        res.push_back(curr);
        if (!prev.contains(curr)){
            //return res;
            qDebug() << "You suck";
            qDebug() << curr;
            qDebug() << end;
            qDebug() << graph[curr];
            throw std::runtime_error("S");
        }
        curr = prev[curr];
    }
    res.push_back(begin);
    //qDebug() << "EndFsts";

    //return res;
    //qDebug() << dists[end];
    return res;

};

template<typename T>
std::vector<T> findPrevious(const Graph<T>& graph,T find,std::vector<T> poses){
    QQueue<T> que;
    QHash<T,bool> checked;
    QHash<T,T> prev;
    checked[find] = 0;
    prev[find] = find;
    que.enqueue(find);
    while (!que.isEmpty()){
        T vert = que.dequeue();
        for (auto con : graph[vert]){
            if (!checked.contains(con)){
                que.enqueue(con);
                checked[con] = 0;
                prev[con] = vert;
            }
        }
    }
    std::vector<T> res;
    for (auto pos : poses){
        res.push_back(prev[pos]);
    }
    return res;
}


template<typename T>
bool dropElementOnce(std::vector<T>& vect,const T& elem){
    int res = -1;
    for (int i = 0;i < vect.size();i++){
        if (vect[i] == elem){
            res = i;
            break;
        }
    }
    if (res != -1){
        vect.erase(vect.begin() + res);
    }
    return (res != -1);
}


/*
template<typename T>
std::vector<std::pair<T,T>> edges(const Graph<T>& graph_){
    std::vector<T>
    Graph<T> graph = graph_;
    for (auto pair : graph){


    }
}
*/

template<typename T>
void dropEdge(Graph<T>& graph,const T& v0,const T& v1){
    bool res = dropElementOnce(graph[v0],v1);
    if (res){
        dropElementOnce(graph[v1],v0);
    }

};

class GraphMap{
private:
    Graph<QPoint> graph_;
    QPoint begin_;
    QPoint end_;
    int interval_;
public:
    GraphMap();
    std::vector<QPoint> potentiallyConnected(const QPoint&);
    GraphMap(const QPoint& vert0,const QPoint& vert1,int interval);
    QPoint findNearest(const QPointF&);
    std::vector<QPointF> getVectors(const QPointF&,const std::vector<QPointF>&);
    void bakeMap(const PolynomCurve&);
    std::vector<QPoint> shortestWay(const QPointF&,const QPointF&);
    void paint(QPainter&);

};








#endif // GRAPHS_H
