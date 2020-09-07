#pragma once

#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <sstream>

namespace Util {

template<typename Container>
bool contains(Container const& c, typename Container::const_reference v) {
    return std::find(c.begin(), c.end(), v) != c.end();
}

template<typename Key, typename Cmp, typename Alloc>
bool contains(std::set<Key,Cmp,Alloc> const& s, Key const& k) {
    return s.find(k) != s.end();
}

template<typename Key, typename Value, typename Cmp, typename Alloc>
bool contains(std::map<Key,Value,Cmp,Alloc> const& m, Key const& k) {
    return m.find(k) != m.end();
}

template<typename Key, typename Value, typename Cmp, typename Alloc>
std::vector<Key> keys(std::map<Key,Value,Cmp,Alloc> const& map) {
    std::vector<Key> keys;
    for(const auto& m: map) {
        keys.push_back(m.first);
    }

    return keys;
}

void sort(auto& container, auto& sorter) {
    std::sort(container.begin(), container.end(), sorter);
}

template<typename Container>
bool equal(const Container& x, const Container& y, auto predicate) {
    return std::equal(x.begin(), x.end(), y.begin(), predicate);
}

std::string toString(const auto& iterable) {
    std::stringstream ss;
    ss << "[ ";
    for(const auto& item: iterable) ss << item << ", ";
    ss << "]";
    return ss.str();
}

}
