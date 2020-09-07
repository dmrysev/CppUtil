#pragma once

#include <functional>
#include <mutex>

namespace Util {

void repeat(int times, auto func) {
    for(int i = 0; i < times; ++i) func();
}

template<typename T>
void forEach(const T& iterable, auto func) {
    std::for_each(iterable.begin(), iterable.end(), func);
}

template<typename ...T>
void forEach(const std::vector<std::tuple<T...>>& iterable, auto func) {
    for(const auto& items: iterable) std::apply(func, items);
}

void forEach(const auto& iterable, auto predicate, auto func) {
    for(const auto& i: iterable) if(predicate(i)) func(i);
}

void transform(auto& iterable, auto func) {
    for(auto& item: iterable) item = func(std::move(item));
}

void transformi(auto& iterable, auto func) {
    size_t i = 0;
    for(auto& value: iterable) value = func(std::move(value), i++);
}

void removeIf(auto& iterable, auto predicate) {
    iterable.erase(std::remove_if(iterable.begin(), iterable.end(), predicate), iterable.end());
}

void remove(auto& iterable, const std::vector<size_t>& indexes) {
    for(size_t i: indexes) iterable.erase(iterable.begin() + i);
}

auto find(const auto& iterable, auto predicate) {
    return std::find_if(iterable.begin(), iterable.end(), predicate);
}

void filter(auto& iterable, auto predicate) {
    removeIf(iterable, [&] (const auto& a) { return !predicate(a); } );
}

std::vector<size_t> findIndexes(const auto& iterable, auto predicate) {
    std::vector<size_t> indexes;
    for(size_t i = 0; i < iterable.size(); ++i)
        if(predicate(i)) indexes.push_back(i);
    return indexes;
}

template<typename T>
std::vector<T> map(const auto& iterable, auto func) {
    std::vector<T> yieldResult;
    for(const auto& item: iterable) {
        auto result = func(item);
        yieldResult.push_back(std::move(result));
    }
    return yieldResult;
}

template<typename T>
std::vector<T> map(auto& iterable, auto func) {
    std::vector<T> yieldResult;
    for(auto& item: iterable) {
        auto result = func(item);
        yieldResult.push_back(std::move(result));
    }
    return yieldResult;
}

}
