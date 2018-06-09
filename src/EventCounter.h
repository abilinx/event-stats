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
        virtual void countEvent(unsigned int timestamp, const std::string& eventTag);
        virtual unsigned int getStat(unsigned int pastSeconds, const std::string& eventTag) const;
    private:
        std::unordered_map<std::string, std::unique_ptr<EventStat>> mEventStats;
    };
}
