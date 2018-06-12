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

    dumpWindows();

    cout << "cleaning up old stats for seconds.." << endl;
    clearWindow(mLastMinuteStat, secondIndex, secondsFromLastUpdate);
    dumpWindows();

    cout << "cleaning up old stats for minutes.." << endl;
    clearWindow(mLastHourStat, minuteIndex, minutesFromLastUpdate);
    dumpWindows();

    cout << "cleaning up old stats for hours.." << endl;
    clearWindow(mLastDayStat, hourIndex, hoursFromLastUpdate);
    dumpWindows();

    cout << "cleaning up old stats for days.." << endl;
    clearWindow(mLastMonthStat, dayIndex, daysFromLastUpdate);
    dumpWindows();

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

    dumpWindows();
    cout << "counting completed." << endl;
}

unsigned int CompressedEventStat::getStat(unsigned int pastSeconds)
{
    ++mNumofGetStats;
    cout << "getting stat in past seconds " << pastSeconds << " in CompressedEventStat.." << endl;

    unsigned int currentTime = getSecondsFromEpoch();
    unsigned int startTime = currentTime - pastSeconds;

    unsigned int currentSecond = currentTime;
    unsigned int currentMinute = currentSecond / 60;  // ignore seconds
    unsigned int currentHour = currentMinute / 60;  // ignore minutes
    unsigned int currentDay = currentHour / 24;  // ignore hours
    cout << "currentSecond: " << currentSecond << ", currentMinute: " << currentMinute << ", currentHour: " << currentHour << ", currentDay: " << currentDay << endl;

    unsigned int endSecondIndex = currentSecond % 60;  // mLastMinuteStat is for every 1 second in a minute
    unsigned int endMinuteIndex = currentMinute % 60;  // mLastHourStat is for every 1 minute in an hour
    unsigned int endHourIndex = currentHour % 24;  // mLastDayStat is for every 1 hour in a day
    unsigned int endDayIndex = currentDay % 30;  // mLastMonthStat is for every 1 day in a month
    cout << "secondIndex: " << endSecondIndex << ", minuteIndex: " << endMinuteIndex << ", hourIndex: " << endHourIndex << ", dayIndex: " << endDayIndex << endl;

    unsigned int startSecond = startTime;
    unsigned int startMinute = startSecond / 60;  // ignore seconds
    unsigned int startHour = startMinute / 60;  // ignore minutes
    unsigned int starttDay = startHour / 24;  // ignore hours
    cout << "startSecond: " << startSecond << ", startMinute: " << startMinute << ", startHour: " << startHour << ", startDay: " << starttDay << endl;

    unsigned int startSecondIndex = startSecond % 60;  // mLastMinuteStat is for every 1 second in a minute
    unsigned int startMinuteIndex = startMinute % 60;  // mLastHourStat is for every 1 minute in an hour
    unsigned int startHourIndex = startHour % 24;  // mLastDayStat is for every 1 hour in a day
    unsigned int startDayIndex = starttDay % 30;  // mLastMonthStat is for every 1 day in a month
    cout << "startSecondIndex: " << startSecondIndex << ", startMinuteIndex: " << startMinuteIndex << ", startHourIndex: " << startHourIndex << ", startDayIndex: " << startDayIndex << endl;

    unsigned int secondsFromLastUpdate = currentSecond - mLastUpdateSecondOfMinute;
    unsigned int minutesFromLastUpdate = currentMinute - mLastUpdateMinuteOfHour;
    unsigned int hoursFromLastUpdate = currentHour - mLastUpdateHourOfDay;
    unsigned int daysFromLastUpdate = currentDay - mLastUpdateDayOfMonth;
    clearWindow(mLastMinuteStat, endSecondIndex, secondsFromLastUpdate);
    clearWindow(mLastHourStat, endMinuteIndex, minutesFromLastUpdate);
    clearWindow(mLastDayStat, endHourIndex, hoursFromLastUpdate);
    clearWindow(mLastMonthStat, endDayIndex, daysFromLastUpdate);

    unsigned int stat = 0;
    if (pastSeconds < 60) {
        stat += sumWindow(mLastMinuteStat, startSecondIndex, endSecondIndex);
    }
    else if (pastSeconds < 3600) {
        stat += sumWindow(mLastHourStat, startMinuteIndex, endMinuteIndex);
    }
    else if (pastSeconds < (3600 * 24)) {
        stat += sumWindow(mLastDayStat, startHourIndex, endHourIndex);
    }
    else {
        stat += sumWindow(mLastMonthStat, startDayIndex, endDayIndex);
    }

    return stat;
}

void CompressedEventStat::dumpWindows() const
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

void CompressedEventStat::clearWindow(vector<unsigned int>& window, unsigned int startIndex, unsigned int num)
{
    unsigned int windowSize = window.size();
    if (num > 0 && startIndex < windowSize) {
        num = min(num, windowSize);
        for (unsigned int i = 0; i < num; ++i) {
            int index = (static_cast<int>(windowSize + startIndex) - static_cast<int>(i)) % windowSize;
            cout << "index: " << index << endl;
            window[index] = 0;
        }
    }
}

unsigned int CompressedEventStat::sumWindow(vector<unsigned int>& window, unsigned int startIndex, unsigned int endIndex)
{
    unsigned int windowSize = window.size();
    unsigned int sum = 0;
    if (startIndex < endIndex) {
        for (unsigned int i = startIndex; i <= endIndex; ++i) {
            sum += window[i];
        }
    }
    else if (endIndex < startIndex) {
        for (unsigned int i = startIndex; i < windowSize; ++i) {
            sum += window[i];
        }
        for (unsigned int i = 0; i <= endIndex; ++i) {
            sum += window[i];
        }
    }
    else {
        sum = window[startIndex];
    }
    return sum;
}
