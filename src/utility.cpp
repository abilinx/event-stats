#include <chrono>
#include "utility.h"
using namespace std;
using namespace eventstats;

unsigned int eventstats::getSecondsFromEpoch()
{
    auto now = chrono::system_clock::now();  // get the current time
    auto nowEpoch = now.time_since_epoch();  // transform the time into a duration since the epoch
    return chrono::duration_cast<chrono::seconds>(nowEpoch).count();
}
