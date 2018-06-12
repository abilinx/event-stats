#include <iostream>
#include <utility>
#include <exception>
#include "utility.h"
#include "EventCounter.h"
#include "ListEventStat.h"
#include "CompressedEventStat.h"
using namespace std;
using namespace eventstats;

EventCounter::EventCounter(unsigned int estimatedEventTypes)
    : mEventStats(2 * estimatedEventTypes),
      mNumofCounts(0),
      mNumofGetStats(0)
{
}

EventCounter::~EventCounter()
{
}

void EventCounter::countEvent(const string& eventTag, unsigned int timestamp)
{
    ++mNumofCounts;
    if (timestamp == 0) {
        timestamp = getSecondsFromEpoch();
    }
    cout << "counting event " << eventTag << " at time " << timestamp << ".." << endl;
    auto eventStatItr = mEventStats.find(eventTag);
    if (eventStatItr != mEventStats.end()) {
        cout << "found event: " << eventStatItr->first << endl;
        eventStatItr->second.count(timestamp);
    }
    else {

//        auto listEventStat = new ListEventStat();
//        listEventStat->count(timestamp);
//        pair<string, EventStat&> eventStatPair(eventTag, *listEventStat);

        auto compressedEventStat = new CompressedEventStat;
        compressedEventStat->count(timestamp);
        pair<string, EventStat&> eventStatPair(eventTag, *compressedEventStat);

        mEventStats.insert(eventStatPair);
    }
}

unsigned int EventCounter::getStat(const string& eventTag, unsigned int pastSeconds)
{
    ++mNumofGetStats;
    cout << "getting stats of " << eventTag << ".." << endl;
    unsigned int stat = 0;
    auto eventStatItr = mEventStats.find(eventTag);
    if (eventStatItr != mEventStats.end()) {
        stat = eventStatItr->second.getStat(pastSeconds);
    }
    else {
        throw out_of_range("\"" + eventTag + "\" is not valid event tag.");
    }
    return stat;
}

void EventCounter::printMetrics() const
{
    cout << "number of counts: " << mNumofCounts << ", number of get stats: " << mNumofGetStats << endl;
}
