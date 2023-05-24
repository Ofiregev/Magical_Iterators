#ifndef ITERATOR_INTERFACE_HPP
#define ITERATOR_INTERFACE_HPP
#include "MagicalContainer.hpp"
template<typename IteratorType>
class Iterator {
public:
    virtual ~Iterator() {}

   virtual IteratorType& operator=(const IteratorType& other) = 0;
    virtual bool operator==(const IteratorType& other) const = 0;
    virtual bool operator!=(const IteratorType& other) const = 0;
    virtual bool operator>(const IteratorType& other) const = 0;
    virtual bool operator<(const IteratorType& other) const = 0;

    virtual int& operator*() = 0;
    virtual IteratorType& operator++() = 0;

    virtual IteratorType begin() const = 0;
    virtual IteratorType end() const = 0;
};

#endif  // ITERATOR_INTERFACE_HPP
