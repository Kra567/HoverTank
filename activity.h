#ifndef ACTIVITY_H
#define ACTIVITY_H
#include <QObject>

class Activity : public QObject
{
    Q_OBJECT
private:
    bool active_ = 1;
public:
    Activity();
    Activity(const Activity&);
    bool isActive();
    //Activity operator=(Activity const&) = default;
public slots:
    void disactivate();
signals:
    void disactivated();


};

template<typename T>
void filterActive(std::vector<T*>& activities){
    std::vector<T*> res;
    for (auto t : activities){
        if (t->isActive()){
            res.push_back(t);
        }
    }
    activities = res;
};

#endif // ACTIVITY_H
