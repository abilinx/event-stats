add_executable(event-stats utility.cpp EventStat.cpp ListEventStat.cpp EventCounter.cpp QueryProcessor.cpp main.cpp)
target_link_libraries(event-stats zmqpp zmq)
