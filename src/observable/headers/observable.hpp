#ifndef INCLUDE_OBSERVABLE_HPP
#define INCLUDE_OBSERVABLE_HPP

#include <functional>
#include <list>
#include <algorithm>

template <class T>
class observable {
private:
    T value;
public:
    const T& getValue() const;

    void setValue(T t);

public:
    class observer {
    public:
        using callback_ftype = std::function<void(const T&, const T&)>;

        explicit observer(callback_ftype update);

        callback_ftype update;

        const callback_ftype && getUpdate() const &&;

        void setUpdate(const callback_ftype &update);
    };

    template<class... Args>
    explicit observable(Args... args);

    // add a observer to observers list
    void add_observer(const observer& add);

    void add_observer(observer&& add);

    void add_observer_emplace(typename observer::callback_ftype callback);

protected:
    using observers_container = std::list<observer>;

    observers_container observers;

    void notify_all(const T &new_value) const;
};

template<class T>
void observable<T>::notify_all(const T &new_value) const {
    for (auto &item : observers) {
        std::invoke(item.getUpdate(), value, new_value);
    }
}

template<class T>
void observable<T>::add_observer(const observable::observer &add) {
    observers.push_back(add);
}

template<class T>
void observable<T>::add_observer(observable::observer &&add) {
    observers.push_back(std::forward<observer>(add));
}

template<class T>
void observable<T>::add_observer_emplace(typename observable::observer::callback_ftype callback) {
    observers.emplace_back(callback);
}

template<class T>
template<class... Args>
observable<T>::observable(Args... args): value{args...} {}

template<class T>
const T& observable<T>::getValue() const {
    return value;
}

template<class T>
void observable<T>::setValue(T t) {
    notify_all(t);
    observable::value = t;
}

template<class T>
observable<T>::observer::observer(observable::observer::callback_ftype update_):
update{update_}{

}

template<class T>
const typename observable<T>::observer::callback_ftype && observable<T>::observer::getUpdate() const && {
    return std::move(update);
}

template<class T>
void observable<T>::observer::setUpdate(const observable::observer::callback_ftype &update_) {
    observer::update = update_;
}

#endif
