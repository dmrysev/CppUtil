#pragma once

#include "date_time.h"
#include <chrono>
#include <iosfwd>

struct DateTimeRange {
    DateTime lower;
    DateTime upper;

    DateTimeRange() = default;
    DateTimeRange(const DateTime& lowerOther, const DateTime& upperOther);
    DateTimeRange(const DateTimeRange& other);
    DateTimeRange(const std::chrono::system_clock::duration& lowerDuration,
                  const std::chrono::system_clock::duration& upperDuration);

    bool containsInclusive(const DateTime& timestamp) const;
    bool hasOverlap(const DateTimeRange& range) const;

    friend std::ostream& operator<<(std::ostream& os, const DateTimeRange& range);
};

bool operator==(const DateTimeRange& a, const DateTimeRange& b);
bool operator<(const DateTimeRange& a, const DateTimeRange& b);
std::ostream& operator<<(std::ostream& os, const DateTimeRange& range);

