#include "util/time.h"

#include <gtest/gtest.h>

using namespace std::chrono_literals;

namespace Util::Test {

class Common_UT_Utils_Time: public testing::Test {};

TEST_F(Common_UT_Utils_Time,
givenTimestampsAndThreshold_callingFindAdjacentTimeRanges_mustReturnTimeRangesSeparatedBySpecifiedThreshold) {
    std::vector<DateTime> timestamps {
        DateTime{1s},
        DateTime{2s},
        DateTime{3s},

        DateTime{11s},
        DateTime{12s},
        DateTime{13s},

        DateTime{1min + 1s},
        DateTime{1min + 2s},
        DateTime{1min + 3s},
    };
    auto testThreshold1 = 1s;
    std::vector<DateTimeRange> expected1 {
        DateTimeRange{DateTime{1s}, DateTime{3s}},
        DateTimeRange{DateTime{11s}, DateTime{13s}},
        DateTimeRange{DateTime{1min + 1s}, DateTime{1min + 3s}}
    };
    auto testThreshold2 = 20s;
    std::vector<DateTimeRange> expected2 {
        DateTimeRange{DateTime{1s}, DateTime{13s}},
        DateTimeRange{DateTime{1min + 1s}, DateTime{1min + 3s}}
    };
    auto testThreshold3 = 2min;
    std::vector<DateTimeRange> expected3 {
        DateTimeRange{DateTime{1s}, DateTime{1min + 3s}}
    };

    ASSERT_EQ(findAdjacentTimeRanges(timestamps, testThreshold1), expected1);
    ASSERT_EQ(findAdjacentTimeRanges(timestamps, testThreshold2), expected2);
    ASSERT_EQ(findAdjacentTimeRanges(timestamps, testThreshold3), expected3);
}

TEST_F(Common_UT_Utils_Time,
givenEmptyTimestampsList_callingFindAdjacentTimeRanges_mustReturnEmptyTimeRangesList) {
    auto result = findAdjacentTimeRanges({}, 1s);
    ASSERT_TRUE(result.empty());
}

TEST_F(Common_UT_Utils_Time,
givenTimestampsListWithOneElement_callingFindAdjacentTimeRanges_mustReturnEmptyTimeRangesList) {
    auto result = findAdjacentTimeRanges({DateTime{1s}}, 1s);
    ASSERT_TRUE(result.empty());
}

TEST_F(Common_UT_Utils_Time,
givenTimestampsListWithTwoEqualElements_callingFindAdjacentTimeRanges_mustReturnEmptyTimeRangesList) {
    auto result = findAdjacentTimeRanges({DateTime{1s}, DateTime{1s}}, 1s);
    ASSERT_TRUE(result.empty());
}

TEST_F(Common_UT_Utils_Time,
givenDateTimeRangeAndTimeDelta_callingSplit_mustReturnListOfDateTimeRangesSplitByTimeDelta) {
    // ARRANGE
    DateTimeRange range{DateTime{1s}, DateTime{14s}};
    std::vector<DateTimeRange> expected {
        {DateTime{1s}, DateTime{6s}},
        {DateTime{6s}, DateTime{11s}},
        {DateTime{11s}, DateTime{14s}}
    };

    // ACT
    auto result = split(range, 5s);

    // ASSERT
    ASSERT_EQ(result, expected);
}

TEST_F(Common_UT_Utils_Time,
givenTwoDateTimeRangea_callingHasOverlap_mustReturnTrueIfTheyOverlapAndFalseIfDont) {
    DateTimeRange range{DateTime{5s}, DateTime{10s}};
    ASSERT_TRUE(range.hasOverlap(DateTimeRange{DateTime{1s}, DateTime{6s}}));
    ASSERT_TRUE(range.hasOverlap(DateTimeRange{DateTime{7s}, DateTime{15s}}));
    ASSERT_TRUE(range.hasOverlap(DateTimeRange{DateTime{7s}, DateTime{9s}}));
    ASSERT_TRUE(range.hasOverlap(DateTimeRange{DateTime{1s}, DateTime{5s}}));
    ASSERT_TRUE(range.hasOverlap(DateTimeRange{DateTime{10s}, DateTime{15s}}));
    ASSERT_TRUE(range.hasOverlap(DateTimeRange{DateTime{3s}, DateTime{13s}}));
    ASSERT_TRUE(range.hasOverlap(DateTimeRange{DateTime{5s}, DateTime{10s}}));

    ASSERT_FALSE(range.hasOverlap(DateTimeRange{DateTime{1s}, DateTime{4s}}));
    ASSERT_FALSE(range.hasOverlap(DateTimeRange{DateTime{11s}, DateTime{15s}}));
}

}
