#include <iostream>
#include <utility>
#include "utility.h"
#include "EventCounter.h"
#include "ListEventStat.h"
#include "CompressedEventStat.h"
using namespace std;
using namespace eventstats;

EventCounter::EventCounter(unsigned int estimatedEventTypes)
    : mEventStats(2 * estimatedEventTypes)
{
}

EventCounter::~EventCounter()
{
}

void EventCounter::countEvent(const string& eventTag, unsigned int timestamp)
{
    cout << "counting event " << eventTag << " at time " << timestamp << ".." << endl;
    if (timestamp == 0) {
        timestamp = getSecondsFromEpoch();
    }
    auto eventStatItr = mEventStats.find(eventTag);
    if (eventStatItr != mEventStats.end()) {
        cout << "found event: " << eventStatItr->first << endl;
        eventStatItr->second.count(timestamp);
    }
    else {
        auto listEventStat = new ListEventStat();
        listEventStat->count(timestamp);
        pair<string, EventStat&> eventStatPair(eventTag, *listEventStat);
        mEventStats.insert(eventStatPair);
    }
}

unsigned int EventCounter::getStat(const string& eventTag, unsigned int pastSeconds) const
{
    cout << "getting stats of " << eventTag << ".." << endl;
    unsigned int stat = 0;
    auto eventStatItr = mEventStats.find(eventTag);
    if (eventStatItr != mEventStats.end()) {
        stat = eventStatItr->second.getStat(pastSeconds);
    }
    else {
        // TODO: Throw out of range exception here.
    }
    return stat;
}
