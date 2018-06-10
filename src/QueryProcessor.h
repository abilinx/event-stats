#pragma once
#include <string>

namespace eventstats
{

    class EventCounter;

    class QueryProcessor
    {
    public:
        QueryProcessor(EventCounter& eventCounter);
        virtual ~QueryProcessor();
        unsigned int getStat(const std::string& query);

    private:
        static bool checkQuery(const std::string& query);

        EventCounter& mEventCounter;
    };
}
