#include <iostream>
#include "CompressedEventStat.h"
using namespace std;
using namespace eventstats;

CompressedEventStat::CompressedEventStat()
{
}

CompressedEventStat::~CompressedEventStat()
{
}

void CompressedEventStat::count(unsigned int timestamp)
{
    cout << "counting event in time " << timestamp << " in CompressedEventStat.." << endl;
    // TODO: Count event.
}

unsigned int CompressedEventStat::getStat(unsigned int pastSeconds) const
{
    cout << "getting stat in past seconds " << pastSeconds << " in CompressedEventStat.." << endl;
    // TODO: Return stat in past seconds.
    return 0;
}
