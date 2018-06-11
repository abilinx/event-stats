#include <iostream>
#include <unistd.h>
#include <zmq.hpp>
using namespace std;

int main()
{
    cout << "query-sender" << endl;

    zmq::context_t zmqContext(1);
    zmq::socket_t querySocket(zmqContext, ZMQ_REQ);
    querySocket.connect("tcp://localhost:9704");

    unsigned long long sentQueriesCount = 0;
    while (true) {
        zmq::message_t zmqMessage(7);
        memcpy(zmqMessage.data(), "60s abc", 7);
        querySocket.send(zmqMessage);
        cout << "\"60s abc\" query is sent." << endl;
        ++sentQueriesCount;

//    	if (sentQueriesCount % 10000 == 0) {
//    		cout << sentQueriesCount << " queries sent." << endl;
//    	}

        zmq::message_t zmqResponse;
        querySocket.recv(&zmqResponse);
        string statStr(static_cast<char*>(zmqResponse.data()), zmqResponse.size());
        cout << "received stat: " << statStr << endl;

        usleep(5000000);
    }

    return 0;
}
