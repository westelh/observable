#ifndef INCLUDE_OBSERVABLE_HPP
#define INCLUDE_OBSERVABLE_HPP

#include <mutex>
#include "../../observer/headers/observer.hpp"

template <class T>
class observable {
        T value_m;
        mutable std::recursive_mutex mutex_m;
    protected:
        inline std::unique_lock<std::recursive_mutex> lock() const noexcept;
    public:
        observable();
        observable(const T&);
        observable(T&&);
        T get() const noexcept;
        void set(const T&) noexcept;
        void set(T&&) noexcept;
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

#endif
