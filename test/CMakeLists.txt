add_executable(test_EventStat ../src/utility.cpp ../src/EventStat.cpp test_EventStat.cpp)
target_link_libraries(test_EventStat gtest gtest_main pthread)

add_executable(test_ListEventStat ../src/utility.cpp ../src/ListEventStat.cpp ../src/EventStat.cpp test_ListEventStat.cpp)
target_link_libraries(test_ListEventStat gtest gtest_main pthread)

add_executable(test_EventCounter ../src/utility.cpp ../src/EventCounter.cpp ../src/EventStat.cpp ../src/ListEventStat.cpp ../src/EventCounter.cpp test_EventCounter.cpp)
target_link_libraries(test_EventCounter gtest gtest_main pthread)

add_executable(test_QueryProcessor ../src/utility.cpp ../src/EventCounter.cpp ../src/EventStat.cpp ../src/ListEventStat.cpp ../src/EventCounter.cpp ../src/QueryProcessor.cpp test_QueryProcessor.cpp)
target_link_libraries(test_QueryProcessor gtest gtest_main pthread)

add_executable(event-sender event_sender.cpp)
target_link_libraries(event-sender zmqpp zmq)

add_executable(query-sender query_sender.cpp)
target_link_libraries(query-sender zmqpp zmq)
