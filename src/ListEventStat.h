#pragma once
#include <queue>
#include <list>
#include "EventStat.h"

namespace eventstats
{
    class ListEventStat: public EventStat
    {
    public:
        ListEventStat();
        virtual ~ListEventStat();
        virtual void count(unsigned int timestamp);
        virtual unsigned int getStat(unsigned int pastSeconds) const;
    private:
//        std::priority_queue<unsigned int, std::list<unsigned int>> mEventTimestamps;
    };
}
