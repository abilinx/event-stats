#include <gtest/gtest.h>
#include <exception>
#include "../src/utility.h"
#include "../src/EventCounter.h"
using namespace std;
using namespace eventstats;

TEST (EventCounter, BasicUsage)
{
    EventCounter eventCounter;
    eventCounter.countEvent("abc", getSecondsFromEpoch() - 10);
    EXPECT_EQ (eventCounter.getStat("abc", 60), 1);
    EXPECT_EQ (eventCounter.getStat("abc", 10), 1);
    EXPECT_EQ (eventCounter.getStat("abc", 5), 0);
    eventCounter.countEvent("def", getSecondsFromEpoch() - 30);
    EXPECT_EQ (eventCounter.getStat("def", 60), 1);
    EXPECT_EQ (eventCounter.getStat("def", 30), 1);
    EXPECT_EQ (eventCounter.getStat("def", 20), 0);
    EXPECT_EQ (eventCounter.getStat("abc", 60), 1);
    EXPECT_EQ (eventCounter.getStat("abc", 10), 1);
    EXPECT_EQ (eventCounter.getStat("abc", 5), 0);
    EXPECT_THROW (eventCounter.getStat("ghi", 5), out_of_range);
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
