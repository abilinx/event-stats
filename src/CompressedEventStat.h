#pragma once
#include <vector>
#include "EventStat.h"

namespace eventstats
{
    class CompressedEventStat: public EventStat
    {
    public:
        CompressedEventStat();
        CompressedEventStat(const CompressedEventStat& src);
        CompressedEventStat(CompressedEventStat&& src) noexcept;

        virtual ~CompressedEventStat();

        virtual CompressedEventStat& operator=(const CompressedEventStat& rhs);
        virtual CompressedEventStat& operator=(CompressedEventStat&& rhs) noexcept;

        virtual void count(unsigned int timestamp = 0);
        virtual unsigned int getStat(unsigned int pastSeconds);

        void dumpWindows() const;

    private:
        void clearWindow(std::vector<unsigned int>& window, unsigned int startIndex, unsigned int num);
        unsigned int sumWindow(std::vector<unsigned int>& window, unsigned int startIndex, unsigned int endIndex);

        std::vector<unsigned int> mLastMinuteStat;
        std::vector<unsigned int> mLastHourStat;
        std::vector<unsigned int> mLastDayStat;
        std::vector<unsigned int> mLastMonthStat;
        unsigned int mLastUpdateSecondOfMinute;
        unsigned int mLastUpdateMinuteOfHour;
        unsigned int mLastUpdateHourOfDay;
        unsigned int mLastUpdateDayOfMonth;
    };
}
