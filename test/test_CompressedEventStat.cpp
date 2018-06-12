#include <gtest/gtest.h>
#include "../src/CompressedEventStat.h"
using namespace std;
using namespace eventstats;

TEST (CompressedEventStat, BasicUsage)
{
    CompressedEventStat compressedEventStat;
    EXPECT_EQ (compressedEventStat.getNumofCounts(), 0);
    EXPECT_EQ (compressedEventStat.getNumofGetStats(), 0);
    compressedEventStat.count();
    EXPECT_EQ (compressedEventStat.getNumofCounts(), 1);
    EXPECT_EQ (compressedEventStat.getNumofGetStats(), 0);
    compressedEventStat.count();
//    EXPECT_EQ (compressedEventStat.getNumofCounts(), 2);
//    EXPECT_EQ (compressedEventStat.getNumofGetStats(), 0);
//    EXPECT_EQ (compressedEventStat.getStat(60), 2);
//    EXPECT_EQ (compressedEventStat.getNumofCounts(), 2);
//    EXPECT_EQ (compressedEventStat.getNumofGetStats(), 1);
//    EXPECT_EQ (compressedEventStat.getStat(60), 2);
//    EXPECT_EQ (compressedEventStat.getNumofCounts(), 2);
//    EXPECT_EQ (compressedEventStat.getNumofGetStats(), 2);
}

//TEST (CompressedEventStat, Copy)
//{
//    CompressedEventStat compressedEventStat1;
//    compressedEventStat1.count();
//    EXPECT_EQ (compressedEventStat1.getStat(60), 1);
//    EXPECT_EQ (compressedEventStat1.getNumofCounts(), 1);
//    EXPECT_EQ (compressedEventStat1.getNumofGetStats(), 1);
//    CompressedEventStat CompressedEventStat2 = compressedEventStat1;
//    EXPECT_EQ (compressedEventStat1.getNumofCounts(), 1);
//    EXPECT_EQ (compressedEventStat1.getNumofGetStats(), 1);
//    EXPECT_EQ (CompressedEventStat2.getNumofCounts(), 1);
//    EXPECT_EQ (CompressedEventStat2.getNumofGetStats(), 1);
//    CompressedEventStat2.count();
//    EXPECT_EQ (CompressedEventStat2.getStat(60), 2);
//    EXPECT_EQ (compressedEventStat1.getNumofCounts(), 1);
//    EXPECT_EQ (compressedEventStat1.getNumofGetStats(), 1);
//    EXPECT_EQ (CompressedEventStat2.getNumofCounts(), 2);
//    EXPECT_EQ (CompressedEventStat2.getNumofGetStats(), 2);
//    CompressedEventStat CompressedEventStat3;
//    CompressedEventStat3 = compressedEventStat1;
//    EXPECT_EQ (compressedEventStat1.getNumofCounts(), 1);
//    EXPECT_EQ (compressedEventStat1.getNumofGetStats(), 1);
//    EXPECT_EQ (CompressedEventStat3.getNumofCounts(), 1);
//    EXPECT_EQ (CompressedEventStat3.getNumofGetStats(), 1);
//    CompressedEventStat3.count();
//    EXPECT_EQ (CompressedEventStat3.getStat(60), 2);
//    EXPECT_EQ (compressedEventStat1.getNumofCounts(), 1);
//    EXPECT_EQ (compressedEventStat1.getNumofGetStats(), 1);
//    EXPECT_EQ (CompressedEventStat3.getNumofCounts(), 2);
//    EXPECT_EQ (CompressedEventStat3.getNumofGetStats(), 2);
//    CompressedEventStat2.count();
//    EXPECT_EQ (CompressedEventStat2.getStat(60), 3);
//    CompressedEventStat3 = compressedEventStat1 = CompressedEventStat2;
//    EXPECT_EQ (compressedEventStat1.getNumofCounts(), 3);
//    EXPECT_EQ (compressedEventStat1.getNumofGetStats(), 3);
//    EXPECT_EQ (CompressedEventStat2.getNumofCounts(), 3);
//    EXPECT_EQ (CompressedEventStat2.getNumofGetStats(), 3);
//    EXPECT_EQ (CompressedEventStat3.getNumofCounts(), 3);
//    EXPECT_EQ (CompressedEventStat3.getNumofGetStats(), 3);
//}

//TEST (CompressedEventStat, Move)
//{
//    CompressedEventStat compressedEventStat1;
//    compressedEventStat1.count();
//    EXPECT_EQ (compressedEventStat1.getStat(60), 1);
//    EXPECT_EQ (compressedEventStat1.getNumofCounts(), 1);
//    EXPECT_EQ (compressedEventStat1.getNumofGetStats(), 1);
//    CompressedEventStat CompressedEventStat2 = move(compressedEventStat1);
//    EXPECT_EQ (compressedEventStat1.getNumofCounts(), 0);
//    EXPECT_EQ (compressedEventStat1.getNumofGetStats(), 0);
//    EXPECT_EQ (CompressedEventStat2.getNumofCounts(), 1);
//    EXPECT_EQ (CompressedEventStat2.getNumofGetStats(), 1);
//    CompressedEventStat2.count();
//    EXPECT_EQ (CompressedEventStat2.getStat(60), 2);
//    EXPECT_EQ (compressedEventStat1.getNumofCounts(), 0);
//    EXPECT_EQ (compressedEventStat1.getNumofGetStats(), 0);
//    EXPECT_EQ (CompressedEventStat2.getNumofCounts(), 2);
//    EXPECT_EQ (CompressedEventStat2.getNumofGetStats(), 2);
//    CompressedEventStat CompressedEventStat3;
//    CompressedEventStat3 = move(CompressedEventStat2);
//    EXPECT_EQ (CompressedEventStat2.getNumofCounts(), 0);
//    EXPECT_EQ (CompressedEventStat2.getNumofGetStats(), 0);
//    EXPECT_EQ (CompressedEventStat3.getNumofCounts(), 2);
//    EXPECT_EQ (CompressedEventStat3.getNumofGetStats(), 2);
//    CompressedEventStat3.count();
//    EXPECT_EQ (CompressedEventStat3.getStat(60), 3);
//    EXPECT_EQ (CompressedEventStat2.getNumofCounts(), 0);
//    EXPECT_EQ (CompressedEventStat2.getNumofGetStats(), 0);
//    EXPECT_EQ (CompressedEventStat3.getNumofCounts(), 3);
//    EXPECT_EQ (CompressedEventStat3.getNumofGetStats(), 3);
//    CompressedEventStat3.count();
//    EXPECT_EQ (CompressedEventStat3.getStat(60), 4);
//    CompressedEventStat2 = move(CompressedEventStat3);
//    compressedEventStat1 = move(CompressedEventStat2);
//    EXPECT_EQ (compressedEventStat1.getNumofCounts(), 4);
//    EXPECT_EQ (compressedEventStat1.getNumofGetStats(), 4);
//    EXPECT_EQ (CompressedEventStat2.getNumofCounts(), 0);
//    EXPECT_EQ (CompressedEventStat2.getNumofGetStats(), 0);
//    EXPECT_EQ (CompressedEventStat3.getNumofCounts(), 0);
//    EXPECT_EQ (CompressedEventStat3.getNumofGetStats(), 0);
//}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
