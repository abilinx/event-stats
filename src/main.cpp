#include <iostream>
#include "../include/event_stats.h"
using namespace std;
using namespace eventstats;

int main()
{
    cout << "event-stats\n";
    EventCounter eventCounter;
    QueryProcessor queryProcessor(eventCounter);
    eventCounter.countEvent("abc");
    eventCounter.countEvent("def");
    eventCounter.countEvent("abc");
    cout << "query result for abc: " << queryProcessor.getStat("1m abc") << endl;
    cout << "query result for def: " << queryProcessor.getStat("1m def") << endl;
	return 0;
}
