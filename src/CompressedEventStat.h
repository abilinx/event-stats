#pragma once
#include "EventStat.h"

namespace eventstats
{
    class CompressedEventStat: public EventStat
    {
    public:
        CompressedEventStat();
        virtual ~CompressedEventStat();
        virtual void count(unsigned int timestamp) = 0;
        virtual unsigned int getStat(unsigned int pastSeconds) const = 0;
    private:
    };
}
