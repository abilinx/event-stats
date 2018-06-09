#include <iostream>
#include "EventStat.h"
using namespace std;
using namespace eventstats;

EventStat::EventStat()
    : mNumofCounts(0),
      mNumofGetStats(0)
{
}

EventStat::EventStat(const EventStat& src)
    : mNumofCounts(src.mNumofCounts),
      mNumofGetStats(src.mNumofGetStats)
{
}

EventStat::EventStat(EventStat&& src) noexcept
{
    mNumofCounts = src.mNumofCounts;
    src.mNumofCounts = 0;
    mNumofGetStats = src.mNumofGetStats;
    src.mNumofGetStats = 0;
}

EventStat::~EventStat()
{
}

EventStat& EventStat::operator=(const EventStat& rhs)
{
    if (this == &rhs) {
        return *this;
    }
    mNumofCounts = rhs.mNumofCounts;
    mNumofGetStats = rhs.mNumofGetStats;
    return *this;
}

EventStat& EventStat::operator=(EventStat&& rhs) noexcept
{
    if (this == &rhs) {
        return *this;
    }
    mNumofCounts = rhs.mNumofCounts;
    rhs.mNumofCounts = 0;
    mNumofGetStats = rhs.mNumofGetStats;
    rhs.mNumofGetStats = 0;
    return *this;
}

void EventStat::count(unsigned int timestamp)
{
    ++mNumofCounts;
    cout << "counting in EventStat class (do nothing).." << endl;
}

unsigned int EventStat::getStat(unsigned int pastSeconds)
{
    ++mNumofGetStats;
    cout << "getting stat in EventStat class (return 0).." << endl;
    return 0;
}

unsigned int EventStat::getNumofCounts() const
{
    return mNumofCounts;
}

unsigned int EventStat::getNumofGetStats() const
{
    return mNumofGetStats;
}
