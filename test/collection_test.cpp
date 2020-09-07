#include "util/collection.h"

#include <gtest/gtest.h>

namespace Util::Test {

TEST(Common_UT_Utils_Collection, sort) {
    std::vector<int> values { 2, 14, 8, 16};
    std::vector<int> expected {2, 8, 14, 16};

    auto intValueSorter = [] (int left, int right) {
        return left < right;
    };
    Util::sort(values, intValueSorter);

    ASSERT_EQ(values, expected);
}

}
