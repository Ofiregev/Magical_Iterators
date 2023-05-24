#ifndef PRIME_ITERATOR_HPP
#define PRIME_ITERATOR_HPP

#include "Iterator.hpp"
#include <cstddef>


class MagicalContainer;
class PrimeIterator  {

private:
    MagicalContainer& container;
    size_t currentIndex;

    PrimeIterator(MagicalContainer& container, size_t currentIndex);

    friend class MagicalContainer;
public:
    PrimeIterator(MagicalContainer& container);
    PrimeIterator(const PrimeIterator& other);
    ~PrimeIterator();

    PrimeIterator& operator=(const PrimeIterator& other);
    bool operator==(const PrimeIterator& other) const;
    bool operator!=(const PrimeIterator& other) const;
    bool operator>(const PrimeIterator& other) const;
    bool operator<(const PrimeIterator& other) const;

    //int& operator*();
    PrimeIterator& operator++();

    static bool isPrime(int num);

    PrimeIterator begin() const;
    PrimeIterator end() const;

};

#endif  // PRIME_ITERATOR_HPP
