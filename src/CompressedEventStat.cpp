#include <iostream>
#include <algorithm>
#include "utility.h"
#include "CompressedEventStat.h"
using namespace std;
using namespace eventstats;

CompressedEventStat::CompressedEventStat()
    : mLastMinuteStat(60),
      mLastHourStat(60),
      mLastDayStat(24),
      mLastMonthStat(30),
      mLastUpdateSecondOfMinute(0),
      mLastUpdateMinuteOfHour(0),
      mLastUpdateHourOfDay(0),
      mLastUpdateDayOfMonth(0)
{
    cout << "default ctor of CompressedEventStat" << endl;
}

CompressedEventStat::CompressedEventStat(const CompressedEventStat& src)
    : EventStat(src),
      mLastMinuteStat(src.mLastMinuteStat),
      mLastHourStat(src.mLastHourStat),
      mLastDayStat(src.mLastDayStat),
      mLastMonthStat(src.mLastMonthStat),
      mLastUpdateSecondOfMinute(src.mLastUpdateSecondOfMinute),
      mLastUpdateMinuteOfHour(src.mLastUpdateMinuteOfHour),
      mLastUpdateHourOfDay(src.mLastUpdateHourOfDay),
      mLastUpdateDayOfMonth(src.mLastUpdateDayOfMonth)
{
    cout << "copy ctor of CompressedEventStat" << endl;
}

CompressedEventStat::CompressedEventStat(CompressedEventStat&& src) noexcept
    : EventStat(move(src)),
      mLastMinuteStat(move(src.mLastMinuteStat)),
      mLastHourStat(move(src.mLastHourStat)),
      mLastDayStat(move(src.mLastDayStat)),
      mLastMonthStat(move(src.mLastMonthStat)),
      mLastUpdateSecondOfMinute(src.mLastUpdateSecondOfMinute),
      mLastUpdateMinuteOfHour(src.mLastUpdateMinuteOfHour),
      mLastUpdateHourOfDay(src.mLastUpdateHourOfDay),
      mLastUpdateDayOfMonth(src.mLastUpdateDayOfMonth)
{
    cout << "move ctor of CompressedEventStat" << endl;
    src.mLastUpdateSecondOfMinute = 0;
    src.mLastUpdateMinuteOfHour = 0;
    src.mLastUpdateHourOfDay = 0;
    src.mLastUpdateDayOfMonth = 0;
}

CompressedEventStat::~CompressedEventStat()
{
    cout << "dtor of CompressedEventStat" << endl;
}

CompressedEventStat& CompressedEventStat::operator=(const CompressedEventStat& rhs)
{
    cout << "copy assignment of CompressedEventStat" << endl;
    if (this == &rhs) {
        return *this;
    }
    EventStat::operator=(rhs);
    mLastMinuteStat = rhs.mLastMinuteStat;
    mLastHourStat = rhs.mLastHourStat;
    mLastDayStat = rhs.mLastDayStat;
    mLastMonthStat = rhs.mLastMonthStat;
    mLastUpdateSecondOfMinute = rhs.mLastUpdateSecondOfMinute;
    mLastUpdateMinuteOfHour = rhs.mLastUpdateMinuteOfHour;
    mLastUpdateHourOfDay = rhs.mLastUpdateHourOfDay;
    mLastUpdateDayOfMonth = rhs.mLastUpdateDayOfMonth;
    return *this;
}

CompressedEventStat& CompressedEventStat::operator=(CompressedEventStat&& rhs) noexcept
{
    cout << "move assignment of CompressedEventStat" << endl;
    if (this == &rhs) {
        return *this;
    }
    EventStat::operator=(move(rhs));
    mLastMinuteStat = move(rhs.mLastMinuteStat);
    mLastHourStat = move(rhs.mLastHourStat);
    mLastDayStat = move(rhs.mLastDayStat);
    mLastMonthStat = move(rhs.mLastMonthStat);
    mLastUpdateSecondOfMinute = move(rhs.mLastUpdateSecondOfMinute);
    mLastUpdateMinuteOfHour = move(rhs.mLastUpdateMinuteOfHour);
    mLastUpdateHourOfDay = move(rhs.mLastUpdateHourOfDay);
    mLastUpdateDayOfMonth = move(rhs.mLastUpdateDayOfMonth);
    return *this;
}

void CompressedEventStat::count(unsigned int timestamp)
{
    ++mNumofCounts;
    if (timestamp == 0) {
        timestamp = getSecondsFromEpoch();
    }
    cout << "counting event in time " << timestamp << " in CompressedEventStat.." << endl;

    unsigned int timestampSecond = timestamp;
    unsigned int timestampMinute = timestampSecond / 60;  // ignore seconds
    unsigned int timestampHour = timestampMinute / 60;  // ignore minutes
    unsigned int timestampDay = timestampHour / 24;  // ignore hours
    cout << "timestampSecond: " << timestampSecond << ", timestampMinute: " << timestampMinute << ", timestampHour: " << timestampHour << ", timestampDay: " << timestampDay << endl;

    unsigned int secondIndex = timestampSecond % 60;  // mLastMinuteStat is for every 1 second in a minute
    unsigned int minuteIndex = timestampMinute % 60;  // mLastHourStat is for every 1 minute in an hour
    unsigned int hourIndex = timestampHour % 24;  // mLastDayStat is for every 1 hour in a day
    unsigned int dayIndex = timestampDay % 30;  // mLastMonthStat is for every 1 day in a month
    cout << "secondIndex: " << secondIndex << ", minuteIndex: " << minuteIndex << ", hourIndex: " << hourIndex << ", dayIndex: " << dayIndex << endl;

    unsigned int secondsFromLastUpdate = timestampSecond - mLastUpdateSecondOfMinute;
    unsigned int minutesFromLastUpdate = timestampMinute - mLastUpdateMinuteOfHour;
    unsigned int hoursFromLastUpdate = timestampHour - mLastUpdateHourOfDay;
    unsigned int daysFromLastUpdate = timestampDay - mLastUpdateDayOfMonth;
    cout << "secondsFromLastUpdate: " << secondsFromLastUpdate << ", minutesFromLastUpdate: " << minutesFromLastUpdate << ", hoursFromLastUpdate: " << hoursFromLastUpdate << ", daysFromLastUpdate: " << daysFromLastUpdate << endl;


    dumpArrays();
    cout << "cleaning up old stats for seconds.." << endl;
    if (secondsFromLastUpdate > 0) {  // if stats is older than 1 seconds
        // zero out seconds from secondIndex backwards to minimum of 60 and secondsFromLastUpdate
        auto minimum = min(secondsFromLastUpdate, static_cast<unsigned int>(60));
        for (unsigned int j = 0; j < minimum; ++j) {
            int index = (static_cast<int>(secondIndex) - static_cast<int>(j)) % 60;
            cout << "index: " << index << endl;
            mLastMinuteStat[index] = 0;
        }
    }
    dumpArrays();

    cout << "cleaning up old stats for minutes.." << endl;
    if (minutesFromLastUpdate > 0) {  // if stats is older than 1 minute
        // zero out minutes from minuteIndex to minimum of 60 and minutesFromLastUpdate
        auto minimum = min(minutesFromLastUpdate, static_cast<unsigned int>(60));
        for (unsigned int j = 0; j < minimum; ++j) {
            int index = (static_cast<int>(minuteIndex) - static_cast<int>(j)) % 60;
            mLastHourStat[index] = 0;
        }
    }
    dumpArrays();

    cout << "cleaning up old stats for hours.." << endl;
    if (hoursFromLastUpdate > 0) {  // if stats is older than 1 hour
        // zero out hours from hourIndex backwards to minimum of 24 and hoursFromLastUpdate
        auto minimum = min(hoursFromLastUpdate, static_cast<unsigned int>(24));
        for (unsigned int j = 0; j < minimum; ++j) {
            int index = (static_cast<int>(hourIndex) - static_cast<int>(j)) % 60;
            mLastDayStat[index] = 0;
        }
    }
    dumpArrays();

    cout << "cleaning up old stats for days.." << endl;
    if (daysFromLastUpdate > 0) {  // if stats is older than 1 day
        // zero out days from dayIndex backwards to minimum of 30 and daysFromLastUpdate
        auto minimum = min(daysFromLastUpdate, static_cast<unsigned int>(30));
        for (unsigned int j = 0; j < minimum; ++j) {
            int index = (static_cast<int>(dayIndex) - static_cast<int>(j)) % 60;
            mLastMonthStat[index] = 0;
        }
    }
    dumpArrays();

    cout << "updating stats.." << endl;
    mLastMinuteStat[secondIndex] += 1;  // update last 1 minute stat
    mLastHourStat[minuteIndex] += 1;  // update last 1 hour stat
    mLastDayStat[hourIndex] += 1;  // update last 1 day stat
    mLastMonthStat[dayIndex] += 1;  // update last 1 month stat

    cout << "updating timestamps.." << endl;
    mLastUpdateSecondOfMinute = timestampSecond;
    mLastUpdateMinuteOfHour = timestampMinute;
    mLastUpdateHourOfDay = timestampHour;
    mLastUpdateDayOfMonth = timestampDay;

    dumpArrays();
    cout << "counting completed." << endl;
}

unsigned int CompressedEventStat::getStat(unsigned int pastSeconds)
{
    ++mNumofGetStats;
    cout << "getting stat in past seconds " << pastSeconds << " in CompressedEventStat.." << endl;
    // TODO: Get stat usinng counters.
    return 0;
}

void CompressedEventStat::dumpArrays() const
{
    cout << "\tminute[";
    for (int i = 0; i < 59; ++i) {
        cout << mLastMinuteStat[i] << ",";
    }
    cout << mLastMinuteStat[59] << "]\n\thour[";
    for (int i = 0; i < 59; ++i) {
        cout << mLastHourStat[i] << ",";
    }
    cout << mLastHourStat[59] << "]\n\tday[";
    for (int i = 0; i < 23; ++i) {
        cout << mLastDayStat[i] << ",";
    }
    cout << mLastDayStat[23] << "]\n\tmonth[";
    for (int i = 0; i < 29; ++i) {
        cout << mLastMonthStat[i] << ",";
    }
    cout << mLastMonthStat[29] << "]\n\t" << mLastUpdateSecondOfMinute << ", " << mLastUpdateMinuteOfHour << ", " << mLastUpdateHourOfDay << ", " << mLastUpdateDayOfMonth << endl;
}

void CompressedEventStat::clearWindow(vector<unsigned int>& window, unsigned int currentIndex, unsigned int clearDistance)
{
    if (clearDistance > 0 && currentIndex < window.size()) {
        clearDistance = min(clearDistance, window.size());
        for (unsigned int i = 0; i < clearDistance; ++i) {
            int index = (static_cast<int>(window.size() + currentIndex) - static_cast<int>(i)) % window.size();
            cout << "index: " << index << endl;
            window[index] = 0;
        }
    }
}
