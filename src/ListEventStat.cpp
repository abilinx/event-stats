#include <iostream>
#include "ListEventStat.h"
using namespace std;
using namespace eventstats;

ListEventStat::ListEventStat()
{
}

ListEventStat::~ListEventStat()
{
}

void ListEventStat::count(unsigned int timestamp)
{
    cout << "counting event in time " << timestamp << " in ListEventStat.." << endl;
//    mEventTimestamps.push(timestamp);
}

unsigned int ListEventStat::getStat(unsigned int pastSeconds) const
{
    cout << "getting stat in past seconds " << pastSeconds << " in ListEventStat.." << endl;
    // TODO: Return stat in past seconds.
    return 0;
}
