#include <iostream>
#include "ListEventStat.h"
using namespace std;
using namespace eventstats;

ListEventStat::ListEventStat()
{
}

ListEventStat::ListEventStat(const ListEventStat& src)
	: EventStat(src)
{
	while (src.mEventTimestamps.size() > 0) {
		mEventTimestamps.push(src.mEventTimestamps.top());
	}
}

ListEventStat::ListEventStat(ListEventStat&& src) noexcept
	: EventStat(move(src))
{
	while (src.mEventTimestamps.size() > 0) {
		mEventTimestamps.push(src.mEventTimestamps.top());
		src.mEventTimestamps.pop();
	}
}

ListEventStat::~ListEventStat()
{
}

ListEventStat& ListEventStat::operator=(const ListEventStat& rhs)
{
	if (this == &rhs) {
		return *this;
	}
	while (mEventTimestamps.size() > 0) {
		mEventTimestamps.pop();
	}
	while (rhs.mEventTimestamps.size() > 0) {
		mEventTimestamps.push(rhs.mEventTimestamps.top());
	}
	return *this;
}

ListEventStat& ListEventStat::operator=(ListEventStat&& rhs) noexcept
{
	if (this == &rhs) {
		return *this;
	}
	EventStat::operator=(move(rhs));
	while (mEventTimestamps.size() > 0) {
		mEventTimestamps.pop();
	}
	while (rhs.mEventTimestamps.size() > 0) {
		mEventTimestamps.push(rhs.mEventTimestamps.top());
		rhs.mEventTimestamps.pop();
	}
	return *this;
}

void ListEventStat::count(unsigned int timestamp)
{
	++mNumofCounts;
    cout << "counting event in time " << timestamp << " in ListEventStat.." << endl;
	mEventTimestamps.push(timestamp);
}

unsigned int ListEventStat::getStat(unsigned int pastSeconds)
{
	++mNumofGetStats;
    cout << "getting stat in past seconds " << pastSeconds << " in ListEventStat.." << endl;
    // TODO: Return stat in past seconds.
    return 0;
}
