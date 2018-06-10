#include <gtest/gtest.h>
#include <chrono>
#include "../src/ListEventStat.h"
using namespace std;
using namespace eventstats;

TEST (ListEventStat, BasicUsage)
{
    ListEventStat listEventStat;
    EXPECT_EQ (listEventStat.getNumofCounts(), 0);
    EXPECT_EQ (listEventStat.getNumofGetStats(), 0);
    listEventStat.count();
    EXPECT_EQ (listEventStat.getNumofCounts(), 1);
    EXPECT_EQ (listEventStat.getNumofGetStats(), 0);
    listEventStat.count();
    EXPECT_EQ (listEventStat.getNumofCounts(), 2);
    EXPECT_EQ (listEventStat.getNumofGetStats(), 0);
    EXPECT_EQ (listEventStat.getStat(60), 2);
    EXPECT_EQ (listEventStat.getNumofCounts(), 2);
    EXPECT_EQ (listEventStat.getNumofGetStats(), 1);
    EXPECT_EQ (listEventStat.getStat(60), 2);
    EXPECT_EQ (listEventStat.getNumofCounts(), 2);
    EXPECT_EQ (listEventStat.getNumofGetStats(), 2);
}

TEST (ListEventStat, Copy)
{
    ListEventStat listEventStat1;
    listEventStat1.count();
    EXPECT_EQ (listEventStat1.getStat(60), 1);
    EXPECT_EQ (listEventStat1.getNumofCounts(), 1);
    EXPECT_EQ (listEventStat1.getNumofGetStats(), 1);
    ListEventStat listEventStat2 = listEventStat1;
    EXPECT_EQ (listEventStat1.getNumofCounts(), 1);
    EXPECT_EQ (listEventStat1.getNumofGetStats(), 1);
    EXPECT_EQ (listEventStat2.getNumofCounts(), 1);
    EXPECT_EQ (listEventStat2.getNumofGetStats(), 1);
    listEventStat2.count();
    EXPECT_EQ (listEventStat2.getStat(60), 2);
    EXPECT_EQ (listEventStat1.getNumofCounts(), 1);
    EXPECT_EQ (listEventStat1.getNumofGetStats(), 1);
    EXPECT_EQ (listEventStat2.getNumofCounts(), 2);
    EXPECT_EQ (listEventStat2.getNumofGetStats(), 2);
    ListEventStat listEventStat3;
    listEventStat3 = listEventStat1;
    EXPECT_EQ (listEventStat1.getNumofCounts(), 1);
    EXPECT_EQ (listEventStat1.getNumofGetStats(), 1);
    EXPECT_EQ (listEventStat3.getNumofCounts(), 1);
    EXPECT_EQ (listEventStat3.getNumofGetStats(), 1);
    listEventStat3.count();
    EXPECT_EQ (listEventStat3.getStat(60), 2);
    EXPECT_EQ (listEventStat1.getNumofCounts(), 1);
    EXPECT_EQ (listEventStat1.getNumofGetStats(), 1);
    EXPECT_EQ (listEventStat3.getNumofCounts(), 2);
    EXPECT_EQ (listEventStat3.getNumofGetStats(), 2);
    listEventStat2.count();
    EXPECT_EQ (listEventStat2.getStat(60), 3);
    listEventStat3 = listEventStat1 = listEventStat2;
    EXPECT_EQ (listEventStat1.getNumofCounts(), 3);
    EXPECT_EQ (listEventStat1.getNumofGetStats(), 3);
    EXPECT_EQ (listEventStat2.getNumofCounts(), 3);
    EXPECT_EQ (listEventStat2.getNumofGetStats(), 3);
    EXPECT_EQ (listEventStat3.getNumofCounts(), 3);
    EXPECT_EQ (listEventStat3.getNumofGetStats(), 3);
}

TEST (ListEventStat, Move)
{
    ListEventStat listEventStat1;
    listEventStat1.count();
    EXPECT_EQ (listEventStat1.getStat(60), 1);
    EXPECT_EQ (listEventStat1.getNumofCounts(), 1);
    EXPECT_EQ (listEventStat1.getNumofGetStats(), 1);
    ListEventStat listEventStat2 = move(listEventStat1);
    EXPECT_EQ (listEventStat1.getNumofCounts(), 0);
    EXPECT_EQ (listEventStat1.getNumofGetStats(), 0);
    EXPECT_EQ (listEventStat2.getNumofCounts(), 1);
    EXPECT_EQ (listEventStat2.getNumofGetStats(), 1);
    listEventStat2.count();
    EXPECT_EQ (listEventStat2.getStat(60), 2);
    EXPECT_EQ (listEventStat1.getNumofCounts(), 0);
    EXPECT_EQ (listEventStat1.getNumofGetStats(), 0);
    EXPECT_EQ (listEventStat2.getNumofCounts(), 2);
    EXPECT_EQ (listEventStat2.getNumofGetStats(), 2);
    ListEventStat listEventStat3;
    listEventStat3 = move(listEventStat2);
    EXPECT_EQ (listEventStat2.getNumofCounts(), 0);
    EXPECT_EQ (listEventStat2.getNumofGetStats(), 0);
    EXPECT_EQ (listEventStat3.getNumofCounts(), 2);
    EXPECT_EQ (listEventStat3.getNumofGetStats(), 2);
    listEventStat3.count();
    EXPECT_EQ (listEventStat3.getStat(60), 3);
    EXPECT_EQ (listEventStat2.getNumofCounts(), 0);
    EXPECT_EQ (listEventStat2.getNumofGetStats(), 0);
    EXPECT_EQ (listEventStat3.getNumofCounts(), 3);
    EXPECT_EQ (listEventStat3.getNumofGetStats(), 3);
    listEventStat3.count();
    EXPECT_EQ (listEventStat3.getStat(60), 4);
    listEventStat2 = move(listEventStat3);
    listEventStat1 = move(listEventStat2);
    EXPECT_EQ (listEventStat1.getNumofCounts(), 4);
    EXPECT_EQ (listEventStat1.getNumofGetStats(), 4);
    EXPECT_EQ (listEventStat2.getNumofCounts(), 0);
    EXPECT_EQ (listEventStat2.getNumofGetStats(), 0);
    EXPECT_EQ (listEventStat3.getNumofCounts(), 0);
    EXPECT_EQ (listEventStat3.getNumofGetStats(), 0);
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
