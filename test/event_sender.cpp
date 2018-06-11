#include <iostream>
#include <unistd.h>
#include <zmq.hpp>
using namespace std;

int main()
{
    cout << "event-sender" << endl;

    zmq::context_t zmqContext(1);
    zmq::socket_t eventSocket(zmqContext, ZMQ_PUSH);
    eventSocket.connect("tcp://localhost:9703");

    unsigned long long sentEventsCount = 0;
    while (true) {
	    zmq::message_t zmqMessage(3);
    	memcpy(zmqMessage.data(), "abc", 3);
    	eventSocket.send(zmqMessage);
        cout << "An event sent with \"abc\" tag." << endl;
    	++sentEventsCount;
//    	if (sentEventsCount % 10000 == 0) {
//    		cout << sentEventsCount << " events sent." << endl;
//    	}
        usleep(5000000);
    }

	return 0;
}
