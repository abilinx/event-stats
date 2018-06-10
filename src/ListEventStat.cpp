#include <iostream>
#include <algorithm>
#include <iterator>
#include "utility.h"
#include "ListEventStat.h"
using namespace std;
using namespace eventstats;

ListEventStat::ListEventStat()
{
    cout << "default ctor of ListEventStat" << endl;
}

ListEventStat::ListEventStat(const ListEventStat& src)
    : EventStat(src),
      mEventTimestamps(src.mEventTimestamps)
{
    cout << "copy ctor of ListEventStat" << endl;
}

ListEventStat::ListEventStat(ListEventStat&& src) noexcept
    : EventStat(move(src)),
      mEventTimestamps(move(src.mEventTimestamps))
{
    cout << "move ctor of ListEventStat" << endl;
}

ListEventStat::~ListEventStat()
{
    cout << "dtor of ListEventStat" << endl;
}

ListEventStat& ListEventStat::operator=(const ListEventStat& rhs)
{
    cout << "copy assignment of ListEventStat" << endl;
	if (this == &rhs) {
		return *this;
	}
    EventStat::operator=(rhs);
    mEventTimestamps.clear();
    mEventTimestamps.insert(mEventTimestamps.begin(), rhs.mEventTimestamps.begin(), rhs.mEventTimestamps.end());
	return *this;
}

ListEventStat& ListEventStat::operator=(ListEventStat&& rhs) noexcept
{
    cout << "move assignment of ListEventStat" << endl;
	if (this == &rhs) {
		return *this;
	}
    EventStat::operator=(move(rhs));
    mEventTimestamps.clear();
    mEventTimestamps = move(rhs.mEventTimestamps);
	return *this;
}

void ListEventStat::count(unsigned int timestamp)
{
	++mNumofCounts;
    if (timestamp == 0) {
        timestamp = getSecondsFromEpoch();
    }
    cout << "counting event in time " << timestamp << " in ListEventStat.." << endl;
    auto insertPosition = lower_bound(mEventTimestamps.begin(), mEventTimestamps.end(), timestamp);
    mEventTimestamps.insert(insertPosition, timestamp);
}

unsigned int ListEventStat::getStat(unsigned int pastSeconds)
{
	++mNumofGetStats;
    cout << "getting stat in past seconds " << pastSeconds << " in ListEventStat.." << endl;
    auto startTimestamp = getSecondsFromEpoch() - pastSeconds;
    cout << "finding timestamps between " << startTimestamp << " and " << getSecondsFromEpoch() << endl;
    auto startPosition = lower_bound(mEventTimestamps.begin(), mEventTimestamps.end(), startTimestamp);
    return distance(startPosition, mEventTimestamps.end());
}
