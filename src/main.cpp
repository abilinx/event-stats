#include <iostream>
#include <exception>
#include <zmq.hpp>
#include "utility.h"
#include "EventCounter.h"
#include "QueryProcessor.h"
using namespace std;
using namespace eventstats;

void test(EventCounter& eventCounter, QueryProcessor& queryProcessor)
{
    eventCounter.countEvent("abc", getSecondsFromEpoch() - 10);
    eventCounter.countEvent("def", getSecondsFromEpoch() - 8);
    eventCounter.countEvent("abc", getSecondsFromEpoch() - 6);
    cout << "query result for abc: " << queryProcessor.getStat("1m abc") << endl;
    cout << "query result for def: " << queryProcessor.getStat("1m def") << endl;

    try {
    	cout << "query result for def: " << queryProcessor.getStat("1h ghi") << endl;
    } catch (const out_of_range& ex) {
    	cerr << "Error: " << ex.what() << endl;
    }

    try {
		cout << "query result for def: " << queryProcessor.getStat("1f ghi") << endl;
	} catch (const InvalidQuery& ex) {
    	cerr << "Error: " << ex.what() << endl;
    }
}

int main()
{
    cout << "event-stats\n";
    EventCounter eventCounter;
    QueryProcessor queryProcessor(eventCounter);

    zmq::context_t zmqContext(1);
    zmq::socket_t eventSocket(zmqContext, ZMQ_PULL);
    eventSocket.bind("tcp://*:9703");

    cout << "waiting on TCP port 9703 for events.." << endl;

    while (true) {
        zmq::message_t zmqMessage;
        eventSocket.recv(&zmqMessage);
        string eventTag(static_cast<char*>(zmqMessage.data()), zmqMessage.size());
        cout << "new event " << eventTag << endl;
        eventCounter.countEvent(eventTag);
        eventCounter.printMetrics();
    }

	return 0;
}
