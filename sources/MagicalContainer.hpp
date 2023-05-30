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
    void swap(size_t index1, size_t index2);

    class AscendingIterator;
    class SideCrossIterator;
    class PrimeIterator;
};

class MagicalContainer::AscendingIterator {
private:
    MagicalContainer& iterator_container;
    size_t currentIndex;

public:
    AscendingIterator( MagicalContainer& container);
    AscendingIterator( MagicalContainer& container, size_t currentIndex);
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
    SideCrossIterator( MagicalContainer& container);
    void arrangeSideCross(MagicalContainer& container);
            SideCrossIterator( MagicalContainer& container, size_t frontIndex, size_t backIndex, bool isFront);
            int operator*() const;
            SideCrossIterator& operator++();
            bool operator==(const SideCrossIterator& other) const;
            bool operator!=(const SideCrossIterator& other) const;
            bool operator>(const SideCrossIterator& other) const;
            bool operator<(const SideCrossIterator& other) const;
    SideCrossIterator begin();
    SideCrossIterator end() const ;
};

class MagicalContainer::PrimeIterator {
private:
    const MagicalContainer& iterator_container;
    size_t currentIndex;

    bool isPrime(int number) const;

public:
    PrimeIterator(const MagicalContainer& container);
    PrimeIterator(const MagicalContainer& container, size_t currentIndex);
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
