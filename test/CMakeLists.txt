add_executable(test_EventStat ../src/EventStat.cpp test_EventStat.cpp)
target_link_libraries(test_EventStat gtest gtest_main pthread)

add_executable(test_ListEventStat ../src/ListEventStat.cpp ../src/EventStat.cpp test_ListEventStat.cpp)
target_link_libraries(test_ListEventStat gtest gtest_main pthread)
