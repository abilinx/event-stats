#include <gtest/gtest.h>
#include "../src/EventStat.h"
using namespace std;
using namespace eventstats;

TEST (EventStat, BasicUsage)
{
    EventStat eventStat;
    EXPECT_EQ (eventStat.getNumofCounts(), 0);
    EXPECT_EQ (eventStat.getNumofGetStats(), 0);
    eventStat.count(10);
    EXPECT_EQ (eventStat.getNumofCounts(), 1);
    EXPECT_EQ (eventStat.getNumofGetStats(), 0);
    eventStat.count(20);
    EXPECT_EQ (eventStat.getNumofCounts(), 2);
    EXPECT_EQ (eventStat.getNumofGetStats(), 0);
    eventStat.getStat(60);
    EXPECT_EQ (eventStat.getNumofCounts(), 2);
    EXPECT_EQ (eventStat.getNumofGetStats(), 1);
    eventStat.getStat(60);
    EXPECT_EQ (eventStat.getNumofCounts(), 2);
    EXPECT_EQ (eventStat.getNumofGetStats(), 2);
}

TEST (EventStat, Copy)
{
    EventStat eventStat1;
    eventStat1.count(10);
    eventStat1.getStat(60);
    EXPECT_EQ (eventStat1.getNumofCounts(), 1);
    EXPECT_EQ (eventStat1.getNumofGetStats(), 1);
    EventStat eventStat2 = eventStat1;
    EXPECT_EQ (eventStat1.getNumofCounts(), 1);
    EXPECT_EQ (eventStat1.getNumofGetStats(), 1);
    EXPECT_EQ (eventStat2.getNumofCounts(), 1);
    EXPECT_EQ (eventStat2.getNumofGetStats(), 1);
    eventStat2.count(20);
    eventStat2.getStat(60);
    EXPECT_EQ (eventStat1.getNumofCounts(), 1);
    EXPECT_EQ (eventStat1.getNumofGetStats(), 1);
    EXPECT_EQ (eventStat2.getNumofCounts(), 2);
    EXPECT_EQ (eventStat2.getNumofGetStats(), 2);
    EventStat eventStat3;
    eventStat3 = eventStat1;
    EXPECT_EQ (eventStat1.getNumofCounts(), 1);
    EXPECT_EQ (eventStat1.getNumofGetStats(), 1);
    EXPECT_EQ (eventStat3.getNumofCounts(), 1);
    EXPECT_EQ (eventStat3.getNumofGetStats(), 1);
    eventStat3.count(20);
    eventStat3.getStat(60);
    EXPECT_EQ (eventStat1.getNumofCounts(), 1);
    EXPECT_EQ (eventStat1.getNumofGetStats(), 1);
    EXPECT_EQ (eventStat3.getNumofCounts(), 2);
    EXPECT_EQ (eventStat3.getNumofGetStats(), 2);
    eventStat2.count(30);
    eventStat2.getStat(60);
    eventStat3 = eventStat1 = eventStat2;
    EXPECT_EQ (eventStat1.getNumofCounts(), 3);
    EXPECT_EQ (eventStat1.getNumofGetStats(), 3);
    EXPECT_EQ (eventStat2.getNumofCounts(), 3);
    EXPECT_EQ (eventStat2.getNumofGetStats(), 3);
    EXPECT_EQ (eventStat3.getNumofCounts(), 3);
    EXPECT_EQ (eventStat3.getNumofGetStats(), 3);
}

TEST (EventStat, Move)
{
    EventStat eventStat1;
    eventStat1.count(10);
    eventStat1.getStat(60);
    EXPECT_EQ (eventStat1.getNumofCounts(), 1);
    EXPECT_EQ (eventStat1.getNumofGetStats(), 1);
    EventStat eventStat2 = move(eventStat1);
    EXPECT_EQ (eventStat1.getNumofCounts(), 0);
    EXPECT_EQ (eventStat1.getNumofGetStats(), 0);
    EXPECT_EQ (eventStat2.getNumofCounts(), 1);
    EXPECT_EQ (eventStat2.getNumofGetStats(), 1);
    eventStat2.count(20);
    eventStat2.getStat(60);
    EXPECT_EQ (eventStat1.getNumofCounts(), 0);
    EXPECT_EQ (eventStat1.getNumofGetStats(), 0);
    EXPECT_EQ (eventStat2.getNumofCounts(), 2);
    EXPECT_EQ (eventStat2.getNumofGetStats(), 2);
    EventStat eventStat3;
    eventStat3 = move(eventStat2);
    EXPECT_EQ (eventStat2.getNumofCounts(), 0);
    EXPECT_EQ (eventStat2.getNumofGetStats(), 0);
    EXPECT_EQ (eventStat3.getNumofCounts(), 2);
    EXPECT_EQ (eventStat3.getNumofGetStats(), 2);
    eventStat3.count(20);
    eventStat3.getStat(60);
    EXPECT_EQ (eventStat2.getNumofCounts(), 0);
    EXPECT_EQ (eventStat2.getNumofGetStats(), 0);
    EXPECT_EQ (eventStat3.getNumofCounts(), 3);
    EXPECT_EQ (eventStat3.getNumofGetStats(), 3);
    eventStat3.count(30);
    eventStat3.getStat(60);
    eventStat2 = move(eventStat3);
    eventStat1 = move(eventStat2);
    EXPECT_EQ (eventStat1.getNumofCounts(), 4);
    EXPECT_EQ (eventStat1.getNumofGetStats(), 4);
    EXPECT_EQ (eventStat2.getNumofCounts(), 0);
    EXPECT_EQ (eventStat2.getNumofGetStats(), 0);
    EXPECT_EQ (eventStat3.getNumofCounts(), 0);
    EXPECT_EQ (eventStat3.getNumofGetStats(), 0);
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
