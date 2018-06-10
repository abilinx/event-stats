#pragma once
#include <unordered_map>
#include <string>
#include <memory>

namespace eventstats
{
    class EventStat;

    class EventCounter
    {
    public:
        EventCounter(unsigned int estimatedEventTypes = 1000);
        virtual ~EventCounter();
        virtual void countEvent(const std::string& eventTag, unsigned int timestamp = 0);
        virtual unsigned int getStat(const std::string& eventTag, unsigned int pastSeconds) const;
    private:
        std::unordered_map<std::string, EventStat&> mEventStats;
    };
}
