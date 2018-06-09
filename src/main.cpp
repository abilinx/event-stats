#include <iostream>
#include "QueryProcessor.h"
#include "EventCounter.h"
using namespace std;
using namespace eventstats;

int main()
{
    cout << "event-stats\n";
    EventCounter eventCounter;
    QueryProcessor queryProcessor(eventCounter);
    eventCounter.countEvent(10, "abc");
    eventCounter.countEvent(12, "def");
    eventCounter.countEvent(15, "abc");
    cout << "query result for abc: " << queryProcessor.getStat("1m abc") << endl;
    cout << "query result for def: " << queryProcessor.getStat("1m def") << endl;
	return 0;
}
