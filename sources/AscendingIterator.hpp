#ifndef ASCENDING_ITERATOR_HPP
#define ASCENDING_ITERATOR_HPP

#include "MagicalContainer.hpp"
#include "Iterator.hpp"
class MagicalContainer;

class AscendingIterator{
    private:
    MagicalContainer& container;
    size_t currentIndex;

    AscendingIterator(MagicalContainer& container, size_t currentIndex);

    friend class MagicalContainer;

public:
    AscendingIterator(MagicalContainer& container);
    AscendingIterator(const AscendingIterator& other);
    ~AscendingIterator();

    AscendingIterator& operator=(const AscendingIterator& other);
    bool operator==(const AscendingIterator& other) const;
    bool operator!=(const AscendingIterator& other) const;
    bool operator>(const AscendingIterator& other) const;
    bool operator<(const AscendingIterator& other) const;

    //int& operator*();
    AscendingIterator& operator++();

   AscendingIterator begin() const;
   AscendingIterator end() const;


};

#endif  // ASCENDING_ITERATOR_HPP
