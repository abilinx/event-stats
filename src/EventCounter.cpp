#include <iostream>
#include <utility>
#include "EventCounter.h"
#include "ListEventStat.h"
#include "CompressedEventStat.h"
using namespace std;
using namespace eventstats;

EventCounter::EventCounter(unsigned int estimatedEventTypes)
//    : mEventStats{2 * estimatedEventTypes}
{
}

EventCounter::~EventCounter()
{
}

void EventCounter::countEvent(unsigned int timestamp, const string& eventTag)
{
    cout << "counting event " << eventTag << " at time " << timestamp << ".." << endl;
    if (mEventStats.count(eventTag) == 1) {
        mEventStats.at(eventTag)->count(timestamp);
    }
    else {
        auto eventStatPtr = make_unique<EventStat>(new ListEventStat());
        eventStatPtr->count(timestamp);
        mEventStats.insert(make_pair(eventTag, eventStatPtr));
    }
}

unsigned int EventCounter::getStat(unsigned int pastSeconds, const string& eventTag) const
{
    cout << "getting stats of " << eventTag << ".." << endl;
    unsigned int stat = 0;
    if (mEventStats.count(eventTag) == 1) {
        const auto& eventStat = mEventStats.at(eventTag);
        stat = eventStat->getStat(pastSeconds);
    }
    else {
        // TODO: Throw out of range exception here.
    }
    return stat;
}
