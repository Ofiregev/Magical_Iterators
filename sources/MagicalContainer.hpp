#ifndef MAGICALCONTAINER_HPP
#define MAGICALCONTAINER_HPP

#include <vector>
namespace ariel
{
    class MagicalContainer
    {
    private:
        std::vector<int> elements_vector;

    public:
        MagicalContainer();
        void addElement(int element);
        void removeElement(int element);
        size_t size() const;
    
        class AscendingIterator;
        class SideCrossIterator;
        class PrimeIterator;
    };

    class MagicalContainer::AscendingIterator
    {
    private:
        MagicalContainer& iterator_container;
        size_t currentIndex;

    public:
        AscendingIterator();
        AscendingIterator(MagicalContainer &container);
        AscendingIterator(MagicalContainer &container, size_t currentIndex);
        AscendingIterator(AscendingIterator &&other) noexcept;
        AscendingIterator(const AscendingIterator &other); // Copy constructor
        ~AscendingIterator();                              // Destructor
        AscendingIterator &operator=(AscendingIterator &&other) noexcept = delete;
        AscendingIterator &operator=(const AscendingIterator &other);
        int operator*() const;
        AscendingIterator &operator++();
        bool operator==(const AscendingIterator &other) const;
        bool operator!=(const AscendingIterator &other) const;
        bool operator>(const AscendingIterator &other) const;
        bool operator<(const AscendingIterator &other) const;
        AscendingIterator begin();
        AscendingIterator end();
    };

    class MagicalContainer::SideCrossIterator
    {
    private:
        MagicalContainer &iterator_container;
        size_t currentIndex;
        size_t startIndex;
        size_t endIndex;
        bool isFront;

    public:
        SideCrossIterator();
        SideCrossIterator(MagicalContainer &container);
        SideCrossIterator(MagicalContainer &container, size_t startIndex, size_t endIndex, bool isFront);
        SideCrossIterator(const SideCrossIterator &other);
        SideCrossIterator(SideCrossIterator &&other) noexcept; // Move constructor declaration
        ~SideCrossIterator();                                  // Destructor
        SideCrossIterator &operator=(const SideCrossIterator &other);
        SideCrossIterator &operator=(SideCrossIterator &&other) noexcept; // Move assignment operator declaration
        void arrangeSideCross(MagicalContainer &container);
        int operator*() const;
        SideCrossIterator &operator++();
        bool operator==(const SideCrossIterator &other) const;
        bool operator!=(const SideCrossIterator &other) const;
        bool operator>(const SideCrossIterator &other) const;
        bool operator<(const SideCrossIterator &other) const;
        SideCrossIterator begin();
        SideCrossIterator end();
    };

    class MagicalContainer::PrimeIterator
    {
    private:
        const MagicalContainer &iterator_container;
        size_t currentIndex;

        bool isPrime(int number) const;

    public:
        PrimeIterator();
        PrimeIterator(const MagicalContainer &container);
        PrimeIterator(const MagicalContainer &container, size_t currentIndex);
        PrimeIterator(const PrimeIterator &other);
        PrimeIterator(PrimeIterator &&other) noexcept; // Move constructor declaration
        ~PrimeIterator();                              // Destructor
        PrimeIterator &operator=(const PrimeIterator &other);
        PrimeIterator &operator=(PrimeIterator &&other) noexcept;
        int operator*() const;
        PrimeIterator &operator++();
        bool operator==(const PrimeIterator &other) const;
        bool operator!=(const PrimeIterator &other) const;
        bool operator>(const PrimeIterator &other) const;
        bool operator<(const PrimeIterator &other) const;
        PrimeIterator begin();
        PrimeIterator end();
    };
}
#endif // MAGICALCONTAINER_HPP
