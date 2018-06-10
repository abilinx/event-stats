#include <iostream>
#include "utility.h"
#include "EventCounter.h"
#include "QueryProcessor.h"
using namespace std;
using namespace eventstats;

int main()
{
    cout << "event-stats\n";
    EventCounter eventCounter;
    QueryProcessor queryProcessor(eventCounter);
    eventCounter.countEvent("abc", getSecondsFromEpoch() - 10);
    eventCounter.countEvent("def", getSecondsFromEpoch() - 8);
    eventCounter.countEvent("abc", getSecondsFromEpoch() - 6);
    cout << "query result for abc: " << queryProcessor.getStat("1m abc") << endl;
    cout << "query result for def: " << queryProcessor.getStat("1m def") << endl;
	return 0;
}
