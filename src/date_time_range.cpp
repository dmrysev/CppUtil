#include "util/date_time_range.h"
#include "util/time.h"

DateTimeRange::DateTimeRange(const DateTime& lowerOther, const DateTime& upperOther):
    lower{lowerOther},
    upper{upperOther}
{}

DateTimeRange::DateTimeRange(const DateTimeRange& other):
    lower{other.lower},
    upper{other.upper}
{}

DateTimeRange::DateTimeRange(const std::chrono::system_clock::duration& lowerDuration,
                             const std::chrono::system_clock::duration& upperDuration):
    lower{DateTime{lowerDuration}},
    upper{DateTime{upperDuration}}
{}

bool DateTimeRange::containsInclusive(const DateTime& timestamp) const {
    return lower <= timestamp && timestamp <= upper;
}

bool DateTimeRange::hasOverlap(const DateTimeRange& range) const {
    return range.lower <= upper && lower <= range.upper;
}

std::ostream& operator<<(std::ostream& os, const DateTimeRange& range) {
    os << Util::to_string(range.lower) << std::string{"; "} << Util::to_string(range.upper);
    return os;
}

bool operator==(const DateTimeRange& a, const DateTimeRange& b) {
    return a.lower == b.lower && a.upper == b.upper;
}

bool operator<(const DateTimeRange& a, const DateTimeRange& b) {
    return a.upper < b.upper;
}
