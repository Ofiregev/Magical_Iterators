#ifndef MAGICALCONTAINER_HPP
#define MAGICALCONTAINER_HPP

#include <vector>
namespace ariel {
class MagicalContainer {
private:
    std::vector<int> elements;

public:
    void addElement(int element);
    void removeElement(int element);
    size_t size() const;

    class AscendingIterator;
    class SideCrossIterator;
    class PrimeIterator;
};

class MagicalContainer::AscendingIterator {
private:
    MagicalContainer& iterator_container;
    size_t currentIndex;

public:
    AscendingIterator();
    AscendingIterator( MagicalContainer& container);
    AscendingIterator( MagicalContainer& container, size_t currentIndex);
    AscendingIterator(const AscendingIterator& other);  // Copy constructor
    ~AscendingIterator();  // Destructor
    AscendingIterator& operator=(const AscendingIterator& other);
    void sortAscending();
    int operator*() const;
    AscendingIterator& operator++();
    bool operator==(const AscendingIterator& other) const;
    bool operator!=(const AscendingIterator& other) const;
    bool operator>(const AscendingIterator& other) const;
    bool operator<(const AscendingIterator& other) const;
    AscendingIterator begin();
    AscendingIterator end();
};

class MagicalContainer::SideCrossIterator {
private:
    MagicalContainer& iterator_container;
    size_t frontIndex;
    size_t backIndex;
    bool isFront;

public:
    SideCrossIterator();
    SideCrossIterator( MagicalContainer& container);
    SideCrossIterator( MagicalContainer& container, size_t frontIndex, size_t backIndex, bool isFront);
    SideCrossIterator(const SideCrossIterator& other);
    ~SideCrossIterator();  // Destructor
    SideCrossIterator& operator=(const SideCrossIterator& other);
    void arrangeSideCross(MagicalContainer& container);
    int operator*() const;
    SideCrossIterator& operator++();
    bool operator==(const SideCrossIterator& other) const;
    bool operator!=(const SideCrossIterator& other) const;
    bool operator>(const SideCrossIterator& other) const;
    bool operator<(const SideCrossIterator& other) const;
    SideCrossIterator begin();
    SideCrossIterator end() ;
};

class MagicalContainer::PrimeIterator {
private:
    const MagicalContainer& iterator_container;
    size_t currentIndex;

    bool isPrime(int number) const;

public:
    
    PrimeIterator();
    PrimeIterator(const MagicalContainer& container);
    PrimeIterator(const MagicalContainer& container, size_t currentIndex);
    PrimeIterator(const PrimeIterator& other);
    ~PrimeIterator();  // Destructor
    PrimeIterator& operator=(const PrimeIterator& other);
    int operator*() const;
    PrimeIterator& operator++();
    bool operator==(const PrimeIterator& other) const;
    bool operator!=(const PrimeIterator& other) const;
    bool operator>(const PrimeIterator& other) const;
    bool operator<(const PrimeIterator& other) const;
    PrimeIterator begin();
    PrimeIterator end();

};
}
#endif // MAGICALCONTAINER_HPP
