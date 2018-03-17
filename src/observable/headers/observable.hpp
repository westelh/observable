#ifndef INCLUDE_OBSERVABLE_HPP
#define INCLUDE_OBSERVABLE_HPP

#include <mutex>
#include <memory>
#include <unordered_map>
#include <stdexcept>
#include "../../observer/headers/observer.hpp"

template <class T>
class observable {
    public:
        using observer_ptr = std::unique_ptr<observer<T>>;
    private:
        T value_m;
        std::unordered_map<std::string, observer_ptr> observers_m;
        mutable std::recursive_mutex mutex_m;
    protected:
        inline std::unique_lock<std::recursive_mutex> lock() const noexcept;
    public:
        observable();
        observable(const T&);
        observable(T&&);
        observable(observable<T>&&);
        T get() const noexcept;
        void set(const T&) noexcept;
        void set(T&&) noexcept;
        void attach(const std::string&, observer_ptr&&);
        void attach(std::string&&, observer_ptr&&);
        const observer_ptr& get_observer_by_key(const std::string& key) const;
};

template <class T>
std::unique_lock<std::recursive_mutex> observable<T>::lock() const noexcept {
    return std::unique_lock<std::recursive_mutex>{mutex_m};
}

template <class T>
observable<T>::observable(): value_m{} {  }

template <class T>
observable<T>::observable(const T& t): value_m{t} {  }

template <class T>
observable<T>::observable(T&& t): value_m{std::forward<T>(t)} {  }

template <class T>
observable<T>::observable(observable<T>&& o):
    value_m{std::move(o.value_m)},
    observers_m{std::move(o.observers_m)},
    mutex_m{} {  }


template <class T>
T observable<T>::get() const noexcept {
    return value_m;
}

template <class T>
void observable<T>::set(const T& t) noexcept {
    auto l = lock();
    value_m = t;
}

template <class T>
void observable<T>::set(T&& t) noexcept {
    auto l = lock();
    value_m = std::forward<T>(t);
}

template <class T>
void observable<T>::attach(const std::string& key, observer_ptr&& val) {
    if (val) {
        auto l = lock();
        observers_m.emplace(std::make_pair(key, observer_ptr{std::move(val)}));
    } else {
        throw std::invalid_argument{"Attached observer doesn't have resource"};
    }
}

template <class T>
void observable<T>::attach(std::string&& key, observer_ptr&& val) {
    if (val) {
        auto l = lock();
        observers_m.emplace(std::make_pair(std::string{std::move(key)}, observer_ptr{std::move(val)}));
    } else {
        throw std::invalid_argument{"Attached observer doesn't have resource"};
    }
}

template <class T>
const typename observable<T>::observer_ptr& observable<T>::get_observer_by_key(const std::string& key) const {
    if (auto itr = observers_m.find(key); itr != observers_m.end()) {
        return itr->second;
    } else {
        throw std::out_of_range{"key:"+key+" not found on observers map"};
    }
}

#endif
