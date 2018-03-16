#ifndef INCLUDE_OBSERVER_HPP
#define INCLUDE_OBSERVER_HPP

template <class T>
class observer {
    public:
        virtual void update(const T& old, const T& new_) = 0;
};

#endif
