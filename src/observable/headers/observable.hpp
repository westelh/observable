#ifndef INCLUDE_OBSERVABLE_HPP
#define INCLUDE_OBSERVABLE_HPP

template <class T>
class observable {
        T value;
    public:
        observable();
        observable(const T&);
        T get() const noexcept;
};


template <class T>
observable<T>::observable(): value{} {  }

template <class T>
observable<T>::observable(const T& t): value{t} {  }

template <class T>
T observable<T>::get() const noexcept {
    return value;
}

#endif
