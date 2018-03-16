#ifndef INCLUDE_OBSERVABLE_HPP
#define INCLUDE_OBSERVABLE_HPP

template <class T>
class observable {
        T value_m;
    public:
        observable();
        observable(const T&);
        observable(T&&);
        T get() const noexcept;
};


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

#endif
