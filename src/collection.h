#pragma once

#include <map>
#include <set>
#include <vector>
#include <algorithm>

namespace ABB::OptiMold::Utils {

template <typename Container>
bool contains(Container const& c, typename Container::const_reference v) {
    return std::find(c.begin(), c.end(), v) != c.end();
}

template <typename Key, typename Cmp, typename Alloc>
bool contains(std::set<Key,Cmp,Alloc> const& s, Key const& k) {
    return s.find(k) != s.end();
}

template <typename Key, typename Value, typename Cmp, typename Alloc>
bool contains(std::map<Key,Value,Cmp,Alloc> const& m, Key const& k) {
    return m.find(k) != m.end();
}

template <typename Key, typename Value, typename Cmp, typename Alloc>
std::vector<Key> keys(std::map<Key,Value,Cmp,Alloc> const& map) {
    std::vector<Key> keys;
    for(const auto& m: map) {
        keys.push_back(m.first);
    }

    return keys;
}

}
