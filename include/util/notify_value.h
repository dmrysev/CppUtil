#pragma once

#include "signal.h"
#include <memory>
#include <shared_mutex>

namespace Util {

template<class T>
class NotifyValue {
public:
    NotifyValue() {
        changed.changedSignal = changedSignal;
        changed.changedSignal2 = changedSignal2;
    };
    NotifyValue(T value) {
        *data = std::move(value);
        changed.changedSignal = changedSignal;
        changed.changedSignal2 = changedSignal2;
    }
    const T& get() const { return *data; }
    void set(T value) {
        *data = std::move(value);
        (*changedSignal)();
        (*changedSignal2)(*data);
    }
    const T& operator() () const { return get(); }
    void operator=(T value) { set(std::move(value)); }

    class {
    public:
        size_t operator+=(std::function<void()> callback) {
            return *changedSignal += callback;
        }

        size_t operator+=(std::function<void(const T&)> callback) {
            return *changedSignal2 += callback;
        }

        void operator-=(size_t connection) {
            *changedSignal -= connection;
            *changedSignal2 -= connection;
        }

    private:
        std::shared_ptr<Signal<void()>> changedSignal = std::make_shared<Signal<void()>>();
        std::shared_ptr<Signal<void(const T&)>> changedSignal2 = std::make_shared<Signal<void(const T&)>>();
        friend class NotifyValue;

    } changed;

private:
    std::shared_ptr<Signal<void()>> changedSignal = std::make_shared<Signal<void()>>();
    std::shared_ptr<Signal<void(const T&)>> changedSignal2 = std::make_shared<Signal<void(const T&)>>();
    std::shared_ptr<T> data = std::make_shared<T>();
};

}
