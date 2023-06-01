#include "activity.h"

Activity::Activity()
{
    active_ = 1;
}

Activity::Activity(const Activity & activity)
{
    active_ = activity.active_;
}

bool Activity::isActive()
{
    return active_;
}



void Activity::disactivate()
{
    active_ = 0;
    disactivated();
    //delete this;
}
/*
void filterActive(std::vector<Activity *> & activities)
{
    std::vector<Activity*> res;
    for (auto act : activities){
        if (act->isActive()){
            res.push_back(act);
        }
    }
    activities = res;
}
*/
