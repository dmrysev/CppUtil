#include "util/time.h"
#include "util/functional.h"

#include <sstream>
#include <iomanip>

using namespace std::chrono;


namespace Util {

tm parse_time(const std::string& time_str)
{
    tm time = {};
    std::istringstream ss(time_str);
    ss >> std::get_time(&time, "%H:%M:%S");
    return time;
}


tm timetotm(time_t secondsUTC) {
    struct tm* ptm = gmtime(&secondsUTC);

    struct tm stm = *ptm;
    stm.tm_year += 1900;
    ++stm.tm_mon;

    return stm;
}

time_t time_now() {
    auto timePoint = system_clock::now();
    time_t time = system_clock::to_time_t(timePoint);

    return time;
}

time_t time_now_ns() {
    std::chrono::high_resolution_clock m_clock;
    return std::chrono::duration_cast<std::chrono::nanoseconds>
              (m_clock.now().time_since_epoch()).count();
}

void runtime_measurement::start() {
    start_point = steady_clock::now();
}

double runtime_measurement::stop() {
    auto endPoint = steady_clock::now();
    auto totalDuration = duration_cast<microseconds>(endPoint - start_point).count();
    auto totalDuration_ms = static_cast<double>(totalDuration / 1000);

    return totalDuration_ms;
}

system_clock::time_point now_ms() {
    return time_point_cast<milliseconds>(system_clock::now());
}

time_t timepointToSeconds(system_clock::time_point timepoint) {
    auto timepointSec = std::chrono::time_point_cast<std::chrono::seconds>(timepoint);
    return timepointSec.time_since_epoch().count();
}

std::string to_string(std::chrono::system_clock::time_point timepoint)
{
    std::time_t tt = std::chrono::system_clock::to_time_t(timepoint);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&tt), "%Y-%m-%d %H:%M:%S");
    auto ms = duration_cast<milliseconds>(timepoint.time_since_epoch()) % 1000;
    ss << '.' << std::setfill('0') << std::setw(3) << ms.count();
    return ss.str();
}

std::vector<DateTimeRange> findAdjacentTimeRanges(const std::vector<DateTime>& timestamps,
                                                  std::chrono::system_clock::duration threshold) {
    if(timestamps.size() <= 1) return {};
    std::vector<DateTimeRange> ranges;
    auto moreThanThreshold = [&threshold] (const DateTime& start, const DateTime& end) {
        return (end - start) > threshold;
    };
    auto it = timestamps.begin();
    while(true) {
        DateTime start = *it;
        it = std::adjacent_find(it, timestamps.end(), moreThanThreshold);
        if(it != timestamps.end()) {
            DateTime end = *it;
            if(end > start) ranges.push_back({start, end});
            ++it;
        }
        else {
            DateTime end = timestamps.back();
            if(end > start) ranges.push_back({start, end});
            break;
        }
    }
    return ranges;
}

std::vector<DateTime> durationsToDateTime(const std::vector<std::chrono::system_clock::duration>& durations) {
    auto durationToDateTime = [] (const system_clock::duration& duration) { return DateTime{duration}; };
    return Util::map<DateTime>(durations, durationToDateTime);
}

std::vector<DateTimeRange> split(const DateTimeRange& range, const system_clock::duration& timeDelta) {
    std::vector<DateTimeRange> ranges;
    auto to = DateTime{0s};
    for(auto from = range.lower; to < range.upper;) {
        to = from + timeDelta;
        if(to > range.upper) to = range.upper;
        ranges.push_back({from, to});
        from = to;
    }
    return ranges;
}

std::optional<DateTimeRange> findRange(const std::vector<DateTimeRange>& ranges, const DateTime& timepoint) {
    for(const auto& range: ranges) {
        if(range.containsInclusive(timepoint)) return range;
    }
    return {};
}

bool contains(const std::vector<DateTimeRange>& ranges, const DateTime& timepoint) {
    for(const auto& range: ranges) {
        if(range.containsInclusive(timepoint)) return true;
    }
    return false;
}

}
