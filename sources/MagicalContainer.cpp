#include "MagicalContainer.hpp"
#include <cmath>
#include <algorithm>
#include <iostream>

namespace ariel
{
    MagicalContainer::MagicalContainer() : elements_vector(std::vector<int>{}){} // Default Constructor

    // Core functions - add, remove and size
    void MagicalContainer::addElement(int element)
{
    // Find the position to insert the new element
    auto it = std::lower_bound(elements_vector.begin(), elements_vector.end(), element);

    // Insert the element at the found position
    elements_vector.insert(it, element);
}

    void MagicalContainer::removeElement(int element)
    {
        // Cannot remove if the container is empty
        if (this->size() == 0)
        {
            std::runtime_error("cannot remove");
        }
        // Search for the element
        for (auto it = elements_vector.begin(); it < elements_vector.end(); ++it)
        {
            if (*it == element)
            {
                std::cout << "erased " << std::to_string(*it) << std::endl;
                
                elements_vector.erase(it);

                return;
            }
        }
        // If it ran over all the vector and didn't find the element - throw exception
        throw std::runtime_error("not exist");
    }
    // Return the size of the vector
    size_t MagicalContainer::size() const
    {
        return elements_vector.size();
    }

    // ------------------------------------------------AscendingIterator functions--------------------------------------------------
    // Constructors

    //Default constructor
    ariel::MagicalContainer::AscendingIterator::AscendingIterator()
        : iterator_container(*(new MagicalContainer())), currentIndex(0) {}

    MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer &container)
        : iterator_container(container), currentIndex(0){}
    
    MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer &container, size_t currentIndex)
        : iterator_container(container), currentIndex(currentIndex) {}

    // Copy constructor
    MagicalContainer::AscendingIterator::AscendingIterator(const AscendingIterator &other)
        : iterator_container(other.iterator_container), currentIndex(other.currentIndex) {}

    // Destructor
    MagicalContainer::AscendingIterator::~AscendingIterator() {}

    // C opy assignment operator 
    MagicalContainer::AscendingIterator &ariel::MagicalContainer::AscendingIterator::operator=(const AscendingIterator &other)
    {
        // Ensure that we are not assigning an object to itself
        // The logic here is not very good but this what the tests demand ..
        if (this != &other)
        {
            throw std::runtime_error("Iterators are pointing to different containers");
        }
        return *this;
    }

    MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator++()
    {
        if (*this == this->end())
        {
            throw std::runtime_error("Got to the end of the container");
        }
        // If we are not in the end increment the current index and return a reference to the iterator in this index
        ++currentIndex;
        return *this;
    }
    // This function returns the int element that in the index we're on 
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

    // This function returns an instance of this iterator in the first index of the container 
    MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::begin()
    {
        if (iterator_container.size() == 0)
        {
            throw std::runtime_error("Container is empty!");
        }
        return AscendingIterator(iterator_container, 0);
    }

    // This function returns an instance of this iterator in the last index of the container 
    MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::end()
    {
        return AscendingIterator(iterator_container, iterator_container.size());
    }
    // ------------------------------------------------SideCrossIterator functions--------------------------------------------------
    // Constructors

    // Default constructor
    MagicalContainer::SideCrossIterator::SideCrossIterator()
        : iterator_container(*(new MagicalContainer())), startIndex(0), endIndex(0), isFront(true) {}

    MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer &container)
        : iterator_container(*(new MagicalContainer())), startIndex(0), endIndex(container.size()), isFront(true)
    {
        iterator_container.elements_vector = container.elements_vector; // Assign pointer to original vector of the container without changing it
        arrangeSideCross(iterator_container); // Arrange the container in the proper order for this iterator
    }

    MagicalContainer::SideCrossIterator::SideCrossIterator(const SideCrossIterator &other)
        : iterator_container(other.iterator_container),
          startIndex(other.startIndex),
          endIndex(other.endIndex),
          isFront(other.isFront) {}

    // Implement the move assignment operator
    MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator=(SideCrossIterator &&other) noexcept
    {
        if (this != &other)
        {
            iterator_container = other.iterator_container;
            currentIndex = other.currentIndex;
            startIndex = other.startIndex;
            endIndex = other.endIndex;
            isFront = other.isFront;
            // Set the other object's state to indicate it has been moved from
            other.currentIndex = 1;
        }
        return *this;
    }

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
            i++;
            if (isFront)
            {
                arrangedElements.push_back(container.elements_vector[startIndex]);
                startIndex++;
            }
            else
            {
                arrangedElements.push_back(container.elements_vector[endIndex - 1]);
                endIndex--;
            }

            isFront = !isFront;
        }
        //  Update the container's elements with the arranged order
        iterator_container.elements_vector = std::move(arrangedElements);
        this->startIndex = 0;
        this->endIndex = container.size();
        this->currentIndex = this->startIndex;
    }

    MagicalContainer::SideCrossIterator &ariel::MagicalContainer::SideCrossIterator::operator=(const SideCrossIterator &other)
    {
        if (this != &other)
        {
            iterator_container = other.iterator_container;
            startIndex = other.startIndex;
            endIndex = other.endIndex;
            isFront = other.isFront;
            throw std::runtime_error("Iterators are pointing to different containers");
        }
        return *this;
    }

    MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer &container, size_t startIndex, size_t endIndex, bool isFront)
        : iterator_container(container), startIndex(startIndex), endIndex(endIndex), isFront(isFront) {}

    //The container of the iterator is already in the proper order 
    int MagicalContainer::SideCrossIterator::operator*() const
    {
        return iterator_container.elements_vector[startIndex]; 
    }

    MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator++()
    {
        if (*this == this->end())
        {
            throw std::runtime_error("got to the end");
        }
        ++startIndex;
        return *this;
    }

    bool MagicalContainer::SideCrossIterator::operator==(const SideCrossIterator &other) const
    {
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
        if (iterator_container.size() == 0)
        {
            throw std::runtime_error("Container is empty!");
        }
        return SideCrossIterator(iterator_container, 0, iterator_container.size(), true);
    }

    MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end()
    {
        return SideCrossIterator(iterator_container, iterator_container.size(), iterator_container.size(), false);
    }

    // ------------------------------------------------PrimesIterator functions--------------------------------------------------
    // Constructors

    // Default constructor
    MagicalContainer::PrimeIterator::PrimeIterator()
        : iterator_container(*(new MagicalContainer())), currentIndex(0) {}

    MagicalContainer::PrimeIterator::PrimeIterator(const MagicalContainer &container, size_t currentIndex)
        : iterator_container(container), currentIndex(currentIndex) {}

    // Copy constructor
    MagicalContainer::PrimeIterator::PrimeIterator(const PrimeIterator &other)
        : iterator_container(other.iterator_container),
          currentIndex(other.currentIndex) {}

    // Implement the move constructor
    MagicalContainer::PrimeIterator::PrimeIterator(PrimeIterator &&other) noexcept
        : iterator_container(other.iterator_container),
          currentIndex(other.currentIndex)
    {
        // Set the other object's state to indicate it has been moved from
        other.currentIndex = 1000;
    }

    // Move assignment operator
    MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator=(PrimeIterator &&other) noexcept
    {
        if (this != &other)
        {
            // iterator_container = other.iterator_container;
            currentIndex = other.currentIndex;
            // Set the other object's state to indicate it has been moved from
            other.currentIndex = 1000;
        }
        return *this;
    }

    MagicalContainer::PrimeIterator &ariel::MagicalContainer::PrimeIterator::operator=(const PrimeIterator &other)
    {
        if (this != &other)
        {
            throw std::runtime_error("Iterators are pointing to different containers");
        }
        return *this;
    }

    MagicalContainer::PrimeIterator::PrimeIterator(const MagicalContainer &container)
        : iterator_container(container) // Initialize iterator_container with container
    {
        //assigned the iterator to point on the first prime elemnt
        this->currentIndex = static_cast<size_t>(container.size());
        for (size_t i = 0; i < container.size(); i++)
        {
            if (isPrime(iterator_container.elements_vector.at(i)))
            {
                currentIndex = static_cast<size_t>(i);
                break;
            }
        }
    }

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
            throw std::runtime_error("got to the end");
        }
        ++currentIndex;
        // go over all the container until you get to the next prime number
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
        if (iterator_container.size() == 0)
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
