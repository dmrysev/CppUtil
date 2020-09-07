#pragma once

#include "date_time_range.h"

#include <ctime>
#include <chrono>
#include <string>
#include <vector>
#include <optional>

namespace Util {

    std::tm timetotm(time_t secondsUTC);

    time_t time_now();
    time_t time_now_ns();

    class runtime_measurement
    {
    public:
        void start();
        double stop();

    private:
        std::chrono::steady_clock::time_point start_point;
    };

    // parse HH:MM:SS time string
    std::tm parse_time(const std::string& time_str);

    std::string to_string(std::chrono::system_clock::time_point timepoint);

    std::chrono::system_clock::time_point now_ms();

    time_t timepointToSeconds(std::chrono::system_clock::time_point timepoint);

    // Assumes that:
    // - timestamps are sorted in ascending order
    std::vector<DateTimeRange> findAdjacentTimeRanges(const std::vector<DateTime>& timestamps,
                                                      std::chrono::system_clock::duration threshold);

    std::vector<DateTime> durationsToDateTime(const std::vector<std::chrono::system_clock::duration>& durations);
    std::vector<DateTimeRange> split(const DateTimeRange& range, const std::chrono::system_clock::duration& timeDelta);
    std::optional<DateTimeRange> findRange(const std::vector<DateTimeRange>& ranges, const DateTime& timepoint);
    bool contains(const std::vector<DateTimeRange>& ranges, const DateTime& timepoint);
}
