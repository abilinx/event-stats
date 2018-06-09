add_executable(test_EventStat ../src/EventStat.cpp test_EventStat.cpp)
target_link_libraries(test_EventStat gtest gtest_main pthread)
