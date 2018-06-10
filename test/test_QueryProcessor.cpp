#include <gtest/gtest.h>
#include "../src/utility.h"
#include "../src/EventCounter.h"
#include "../src/QueryProcessor.h"
using namespace std;
using namespace eventstats;

TEST (QueryProcessor, BasicUsage)
{
    EventCounter eventCounter;
    QueryProcessor queryProcessor(eventCounter);
    EXPECT_THROW (queryProcessor.getStat("60s abc"), out_of_range);
    eventCounter.countEvent("abc", getSecondsFromEpoch() - 10);
    EXPECT_EQ (queryProcessor.getStat("60s abc"), 1);
    EXPECT_EQ (queryProcessor.getStat("10s abc"), 1);
    EXPECT_EQ (queryProcessor.getStat("5s abc"), 0);
    eventCounter.countEvent("abc", getSecondsFromEpoch() - (60 + 10));
    EXPECT_EQ (queryProcessor.getStat("1m abc"), 1);
    EXPECT_EQ (queryProcessor.getStat("2m abc"), 2);
    eventCounter.countEvent("abc", getSecondsFromEpoch() - (3600 + 100));
    EXPECT_EQ (queryProcessor.getStat("1h abc"), 2);
    EXPECT_EQ (queryProcessor.getStat("2h abc"), 3);
    eventCounter.countEvent("abc", getSecondsFromEpoch() - (3600 * 24 + 1000));
    EXPECT_EQ (queryProcessor.getStat("1d abc"), 3);
    EXPECT_EQ (queryProcessor.getStat("2d abc"), 4);
}

TEST (QueryProcessor, QueryPattern)
{
    EventCounter eventCounter;
    QueryProcessor queryProcessor(eventCounter);
    eventCounter.countEvent("abc", getSecondsFromEpoch() - 10);
    EXPECT_EQ (queryProcessor.getStat("60s abc"), 1);    
    EXPECT_THROW (queryProcessor.getStat("s abc"), InvalidQuery);
    EXPECT_THROW (queryProcessor.getStat("60g abc"), InvalidQuery);
    EXPECT_THROW (queryProcessor.getStat("60sabc"), InvalidQuery);
    EXPECT_THROW (queryProcessor.getStat("60s  abc"), InvalidQuery);
    EXPECT_THROW (queryProcessor.getStat("60s abc_"), InvalidQuery);
    EXPECT_THROW (queryProcessor.getStat("60s 4abc"), InvalidQuery);
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
