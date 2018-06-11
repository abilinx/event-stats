#include <iostream>
#include <exception>
#include <thread>
#include <zmq.hpp>
#include "utility.h"
#include "EventCounter.h"
#include "QueryProcessor.h"
using namespace std;
using namespace eventstats;

void handleEvents(zmq::context_t& zmqContext, EventCounter& eventCounter)
{
    cout << "The thread handling the events started." << endl;

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

    cout << "The thread handling the events stopped." << endl;
}

void handleQueries(zmq::context_t& zmqContext, QueryProcessor& queryProcessor)
{
    cout << "The thread handling the queries started." << endl;

    zmq::socket_t querySocket(zmqContext, ZMQ_REP);
    querySocket.bind("tcp://*:9704");

    cout << "waiting on TCP port 9704 for queries.." << endl;

    while (true) {
        zmq::message_t zmqRequest;
        querySocket.recv(&zmqRequest);
        string query(static_cast<char*>(zmqRequest.data()), zmqRequest.size());
        cout << "received query: " << query << endl;

        string respStr = "";
        try {
            auto stat = queryProcessor.getStat(query);
            respStr = to_string(stat);
        } catch (const out_of_range& ex) {
            respStr = ex.what();
        } catch (const InvalidQuery& ex) {
            respStr = ex.what();
        } catch (const exception& ex) {
            respStr = ex.what();
        }

        zmq::message_t zmqResponse(respStr.size());
        memcpy(zmqResponse.data(), respStr.c_str(), respStr.size());
        querySocket.send(zmqResponse);
        cout << "replied response: " << respStr << endl;
    }

    cout << "The thread handling the quereis stopped." << endl;
}

int main()
{
    cout << "event-stats" << endl;

    EventCounter eventCounter;
    QueryProcessor queryProcessor(eventCounter);

    zmq::context_t zmqContext(1);

    cout << "Creating handler threads.." << endl;
    thread eventHandler(handleEvents, ref(zmqContext), ref(eventCounter));
    thread queryHandler(handleQueries, ref(zmqContext), ref(queryProcessor));
    cout << "Waiting for handler threads to join.." << endl;
    eventHandler.join();
    queryHandler.join();
    cout << "Handler threads joined." << endl;

    cout << "End of execution!" << endl;
	return 0;
}
