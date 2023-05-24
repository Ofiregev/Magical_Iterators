#ifndef SIDE_CROSS_ITERATOR_HPP
#define SIDE_CROSS_ITERATOR_HPP
#include <cstddef> 
#include "Iterator.hpp"
class MagicalContainer;

class SideCrossIterator  {
private:
    MagicalContainer& container;
    size_t currentIndex;

    SideCrossIterator(MagicalContainer* container, size_t currentIndex);

    friend class MagicalContainer;
public:
    SideCrossIterator(MagicalContainer& container);
    SideCrossIterator(const SideCrossIterator& other);
    ~SideCrossIterator();

    SideCrossIterator begin() const;
    SideCrossIterator end() const ;
    SideCrossIterator& operator=(const SideCrossIterator& other);
    bool operator==(const SideCrossIterator& other) const;
    bool operator!=(const SideCrossIterator& other) const;
    bool operator>(const SideCrossIterator& other) const;
    bool operator<(const SideCrossIterator& other) const;

   // int& operator*();
    SideCrossIterator& operator++();


};

#endif  // SIDE_CROSS_ITERATOR_HPP
