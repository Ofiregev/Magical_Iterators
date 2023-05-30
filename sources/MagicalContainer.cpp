#include "MagicalContainer.hpp"
#include <cmath>
#include <algorithm>
#include <iostream>

namespace ariel
{
    // Core function - add, remove and size
    void MagicalContainer::addElement(int element)
    {
        elements_vector.push_back(element);
    }

    void MagicalContainer::removeElement(int element)
    {
        if (this->size() == 0)
        {
            throw("cannot remove");
        }
        for (auto it = elements_vector.begin(); it <= elements_vector.end(); ++it)
        {

            if (*it == element)
            {
                elements_vector.erase(it);
                std::cout << "erased " << std::to_string(*it) << std::endl;
                ;
                return;
            }
        }
    }

    size_t MagicalContainer::size() const
    {
        return elements_vector.size();
    }

    // ------------------------------------------------AscendingIterator functions--------------------------------------------------
    // Constructors
    ariel::MagicalContainer::AscendingIterator::AscendingIterator()
        : iterator_container(*(new MagicalContainer())), currentIndex(0) {}

    MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer &container)
        : iterator_container(container), currentIndex(0)
    {
        sortAscending();
    }

    MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer &container, size_t currentIndex)
        : iterator_container(container), currentIndex(currentIndex) {}

    MagicalContainer::AscendingIterator::AscendingIterator(const AscendingIterator &other)
        : iterator_container(other.iterator_container), currentIndex(other.currentIndex) {}

    // Destructor
    MagicalContainer::AscendingIterator::~AscendingIterator() {}

    void MagicalContainer::AscendingIterator::sortAscending()
    {
        std::sort(iterator_container.elements_vector.begin(), iterator_container.elements_vector.end());
    }

    MagicalContainer::AscendingIterator &ariel::MagicalContainer::AscendingIterator::operator=(const AscendingIterator &other)
    {
        if (this != &other)
        {
            iterator_container = other.iterator_container;
            currentIndex = other.currentIndex;
        }
        return *this;
    }

    MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator++()
    {
        ++currentIndex;
        return *this;
    }
    int MagicalContainer::AscendingIterator::operator*() const
    {
        return iterator_container.elements_vector[currentIndex];
    }

    bool MagicalContainer::AscendingIterator::operator==(const AscendingIterator &other) const
    {
        return currentIndex == other.currentIndex;
    }

    bool MagicalContainer::AscendingIterator::operator!=(const AscendingIterator &other) const
    {
        return !(*this == other);
    }

    bool MagicalContainer::AscendingIterator::operator>(const AscendingIterator &other) const
    {
        return currentIndex > other.currentIndex;
    }

    bool MagicalContainer::AscendingIterator::operator<(const AscendingIterator &other) const
    {
        return currentIndex < other.currentIndex;
    }

    MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::begin()
    {
        if(iterator_container.size() == 0)
        {
            throw("cannot get in the container");
        }
        return AscendingIterator(iterator_container, 0);
    }

    MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::end()
    {
        return AscendingIterator(iterator_container, iterator_container.size());
    }
    // ------------------------------------------------SideCrossIterator functions--------------------------------------------------
    // Constructors
    MagicalContainer::SideCrossIterator::SideCrossIterator()
        : iterator_container(*(new MagicalContainer())), startIndex(0), endIndex(0), isFront(true) {}

    MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer &container)
        : iterator_container(container), startIndex(0), endIndex(0), isFront(true)
    {
        arrangeSideCross(iterator_container);
    }
    MagicalContainer::SideCrossIterator::SideCrossIterator(const SideCrossIterator &other)
        : iterator_container(other.iterator_container),
          startIndex(other.startIndex),
          endIndex(other.endIndex),
          isFront(other.isFront) {}
    // Destructor
    MagicalContainer::SideCrossIterator::~SideCrossIterator() {}

    // This function takes the container of the iterator and arrange it's element by the proper order
    void MagicalContainer::SideCrossIterator::arrangeSideCross(MagicalContainer &container)
    {
        std::vector<int> arrangedElements;
        size_t startIndex = 0;
        size_t endIndex = container.size();

        // Alternate between taking elements from the front and back
        bool isFront = true;
        int i = 0;
        while (startIndex < endIndex)
        {
            // std ::cout << i << std::endl;
            i++;
            if (isFront)
            {
                arrangedElements.push_back(container.elements_vector[startIndex]);
                // std ::cout << container.elements_vector[startIndex] << std::endl;
                startIndex++;
            }
            else
            {
                arrangedElements.push_back(container.elements_vector[endIndex - 1]);
                // std ::cout << container.elements_vector[endIndex -1] << std::endl;
                endIndex--;
            }

            isFront = !isFront;
        }
        // container.removeElement(container.elements_vector[endIndex -1]);
        //  Update the container's elements with the arranged order
        container.elements_vector = std::move(arrangedElements);

        // Update the iterator's indices
        this->startIndex = 0;
        this->endIndex = container.size();
    }

    MagicalContainer::SideCrossIterator &ariel::MagicalContainer::SideCrossIterator::operator=(const SideCrossIterator &other)
    {
        if (this != &other)
        {
            iterator_container = other.iterator_container;
            startIndex = other.startIndex;
            endIndex = other.endIndex;
            isFront = other.isFront;
        }
        return *this;
    }
    MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer &container, size_t startIndex, size_t endIndex, bool isFront)
        : iterator_container(container), startIndex(startIndex), endIndex(endIndex), isFront(isFront) {}

    int MagicalContainer::SideCrossIterator::operator*() const
    {
        return isFront ? iterator_container.elements_vector[startIndex] : iterator_container.elements_vector[endIndex];
    }

    MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator++()
    {
        if (isFront)
        {
            ++startIndex;
            if (startIndex > endIndex)
                startIndex = endIndex; // Make sure startIndex doesn't go beyond endIndex
        }
        else
        {
            --endIndex;
            if (endIndex < startIndex)
                endIndex = startIndex; // Make sure endIndex doesn't go beyond startIndex
        }
        return *this;
    }

    bool MagicalContainer::SideCrossIterator::operator==(const SideCrossIterator &other) const
    {
        // std::cout << "front: " << std::to_string(startIndex) << std::endl;
        // std::cout << "front other: " << std::to_string(other.startIndex) << std::endl;
        // std::cout << "back: " << std::to_string(endIndex) << std::endl;
        // std::cout << "back other: " << std::to_string(other.endIndex) << std::endl;

        return (startIndex == other.startIndex) && (endIndex == other.endIndex);
    }

    bool MagicalContainer::SideCrossIterator::operator!=(const SideCrossIterator &other) const
    {
        return !(*this == other);
    }

    bool MagicalContainer::SideCrossIterator::operator>(const SideCrossIterator &other) const
    {
        return (startIndex > other.startIndex) || (endIndex < other.endIndex);
    }

    bool MagicalContainer::SideCrossIterator::operator<(const SideCrossIterator &other) const
    {
        return (startIndex < other.startIndex) || (endIndex > other.endIndex);
    }

    MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin()
    {
        if(iterator_container.size() == 0)
        {
            throw("cannot get in the container");
        }
        return SideCrossIterator(iterator_container, 0, iterator_container.size(), true);
    }

    MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end()
    {
        return SideCrossIterator(iterator_container, iterator_container.size(), iterator_container.size(), false);
    }

    // ------------------------------------------------PrimesIterator functions--------------------------------------------------
    // Constructors
    MagicalContainer::PrimeIterator::PrimeIterator()
        : iterator_container(*(new MagicalContainer())), currentIndex(0) {}

    MagicalContainer::PrimeIterator::PrimeIterator(const MagicalContainer &container, size_t currentIndex)
        : iterator_container(container), currentIndex(currentIndex) {}

    MagicalContainer::PrimeIterator::PrimeIterator(const PrimeIterator &other)
        : iterator_container(other.iterator_container),
          currentIndex(other.currentIndex) {}

    MagicalContainer::PrimeIterator &ariel::MagicalContainer::PrimeIterator::operator=(const PrimeIterator &other)
    {
        if (this != &other)
        {
            currentIndex = other.currentIndex;
        }
        return *this;
    }

    MagicalContainer::PrimeIterator::PrimeIterator(const MagicalContainer &container)
        : iterator_container(container), currentIndex(0) {}

    // Destructor
    MagicalContainer::PrimeIterator::~PrimeIterator() {}

    bool MagicalContainer::PrimeIterator::isPrime(int number) const
    {
        if (number < 2)
            return false;
        for (int i = 2; i <= std::sqrt(number); ++i)
        {
            if (number % i == 0)
                return false;
        }
        return true;
    }

    int MagicalContainer::PrimeIterator::operator*() const
    {
        return iterator_container.elements_vector[currentIndex];
    }

    MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator++()
    {
        if (*this == this->end())
        {
            throw("got to the end");
        }
        ++currentIndex;
        while (currentIndex <= iterator_container.size() - 1 && !isPrime(iterator_container.elements_vector[currentIndex]))
        {
            ++currentIndex;
        }
        return *this;
    }

    bool MagicalContainer::PrimeIterator::operator==(const PrimeIterator &other) const
    {
        return currentIndex == other.currentIndex;
    }

    bool MagicalContainer::PrimeIterator::operator!=(const PrimeIterator &other) const
    {
        return !(*this == other);
    }

    bool MagicalContainer::PrimeIterator::operator>(const PrimeIterator &other) const
    {
        return currentIndex > other.currentIndex;
    }

    bool MagicalContainer::PrimeIterator::operator<(const PrimeIterator &other) const
    {
        return currentIndex < other.currentIndex;
    }

    MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin()
    {
        if(iterator_container.size() == 0)
        {
            throw("cannot get in the container");
        }
        size_t currentIndex = 0;
        while (currentIndex < iterator_container.size() && !isPrime(iterator_container.elements_vector[currentIndex]))
            ++currentIndex;
        return PrimeIterator(iterator_container, currentIndex);
    }

    MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end()
    {
        return PrimeIterator(iterator_container, iterator_container.size());
    }
}
