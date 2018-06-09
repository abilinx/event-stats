#pragma once

namespace eventstats
{
    class EventStat
    {
    public:
        EventStat();
        EventStat(const EventStat& src);
        EventStat(EventStat&& src) noexcept;

        virtual ~EventStat();

        virtual EventStat& operator=(const EventStat& rhs);
        virtual EventStat& operator=(EventStat&& rhs) noexcept;

        virtual void count(unsigned int timestamp);
        virtual unsigned int getStat(unsigned int pastSeconds);

        unsigned int getNumofCounts() const;
        unsigned int getNumofGetStats() const;

    protected:
        unsigned int mNumofCounts;
        unsigned int mNumofGetStats;
    };
}
