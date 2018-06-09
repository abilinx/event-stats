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
        ListEventStat(const ListEventStat& src);
        ListEventStat(ListEventStat&& src) noexcept;

        virtual ~ListEventStat();

        virtual ListEventStat& operator=(const ListEventStat& rhs);
        virtual ListEventStat& operator=(ListEventStat&& rhs) noexcept;

        virtual void count(unsigned int timestamp);
        virtual unsigned int getStat(unsigned int pastSeconds);

    private:
    	std::priority_queue<unsigned int> mEventTimestamps;
    };
}
