#include <iostream>
#include <sstream>
#include "QueryProcessor.h"
#include "EventCounter.h"
using namespace std;
using namespace eventstats;

QueryProcessor::QueryProcessor(const eventstats::EventCounter& eventCounter)
    : mEventCounter(eventCounter)
{
}

QueryProcessor::~QueryProcessor()
{
}

unsigned int QueryProcessor::getStat(const string& query)
{
    cout << "Query: " << query << endl;
    istringstream queryStream(query);
    string timePart = "";
    string eventTag = "";
    queryStream >> timePart >> eventTag;
    unsigned int pastSeconds = 0;
    string timeValue = timePart.substr(0, timePart.size() - 1);
    unsigned int intTimeValue = stoul(timeValue);

    switch (timePart[timePart.size() - 1]) {
    case 's':
        pastSeconds = intTimeValue;
        break;
    case 'm':
        pastSeconds = intTimeValue * 60;
        break;
    case 'h':
        pastSeconds = intTimeValue * 60 * 60;
        break;
    case 'd':
        pastSeconds = intTimeValue * 60 * 60 * 24;
        break;
    default:
        cerr << "unknown query format" << endl;
        return 0;
    }

    cout << "querying " << eventTag << " event in past " << pastSeconds << " second(s).." << endl;
    return mEventCounter.getStat(eventTag, pastSeconds);
}
