#include "util/functional.h"

#include <gtest/gtest.h>
#include <vector>
#include <list>

namespace Util::Test {

TEST(Common_UT_Utils_Functional, removeIf) {
    auto test = [] (auto predicate) {
        std::vector<int> values { 1, 2, 3, 4, 5 };
        Util::removeIf(values, predicate);
        return values;
    };
    auto predicate1 = [] (int i) { return i > 3; };
    auto expected1 = std::vector<int> {1, 2, 3};
    auto predicate2 = [] (int i) { return i <= 3; };
    auto expected2 = std::vector<int> {4, 5};

    ASSERT_EQ(test(predicate1), expected1);
    ASSERT_EQ(test(predicate2), expected2);
}

TEST(Common_UT_Utils_Functional, filter) {
    std::vector<int> values { 1, 2, 3, 4, 5 };
    auto evenNumbers = [] (int i) { return i % 2 == 0; };
    std::vector<int> expected { 2, 4 };

    Util::filter(values, evenNumbers);

    ASSERT_EQ(values, expected);
}

TEST(Common_UT_Utils_Functional, transform) {
    std::vector<int> values { 1, 2, 3 };
    auto func = [] (int i) { return i + 1; };
    std::vector<int> expected { 2, 3, 4 };

    Util::transform(values, func);

    ASSERT_EQ(values, expected);
}

TEST(Common_UT_Utils_Functional, transformi) {
    std::vector<int> values { 1, 2, 3 };
    auto func = [] (int i, size_t) { return i + 1; };
    std::vector<int> expected { 2, 3, 4 };

    Util::transformi(values, func);

    ASSERT_EQ(values, expected);
}

}
