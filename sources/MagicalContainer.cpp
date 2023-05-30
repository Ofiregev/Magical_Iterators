#include "MagicalContainer.hpp"
#include <cmath>
#include <algorithm>
#include <iostream>

namespace ariel {
    void MagicalContainer::addElement(int element) {
        elements.push_back(element);
    }

    void MagicalContainer::removeElement(int element) {
        if(this->size() == 0)
        {
            throw("cannot remove");
        }
        for (auto it = elements.begin(); it != elements.end(); ++it) {
            if (*it == element) {
                elements.erase(it);
                return;
            }
        }
    }

    size_t MagicalContainer::size() const {
        return elements.size();
    }

    void MagicalContainer::swap(size_t index1, size_t index2) {
        std::swap(elements[index1], elements[index2]);
    }

    MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer& container)
        : iterator_container(container), currentIndex(0) {
        sortAscending();
    }

    MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer& container, size_t currentIndex)
        : iterator_container(container), currentIndex(currentIndex) {}

    void MagicalContainer::AscendingIterator::sortAscending() {
        std::sort(iterator_container.elements.begin(), iterator_container.elements.end());
    }

    int MagicalContainer::AscendingIterator::operator*() const {
        return iterator_container.elements[currentIndex];
    }

    MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator++() {
        ++currentIndex;
        return *this;
    }

    bool MagicalContainer::AscendingIterator::operator==(const AscendingIterator& other) const {
        return currentIndex == other.currentIndex;
    }

    bool MagicalContainer::AscendingIterator::operator!=(const AscendingIterator& other) const {
        return !(*this == other);
    }

    bool MagicalContainer::AscendingIterator::operator>(const AscendingIterator& other) const {
        return currentIndex > other.currentIndex;
    }

    bool MagicalContainer::AscendingIterator::operator<(const AscendingIterator& other) const {
        return currentIndex < other.currentIndex;
    }

    MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::begin() {
        return AscendingIterator(iterator_container, 0);
    }

    MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::end() {
        return AscendingIterator(iterator_container, iterator_container.size());
    }
void MagicalContainer::SideCrossIterator::arrangeSideCross(MagicalContainer& container) {
    std::vector<int> arrangedElements;
    size_t frontIndex = 0;
    size_t backIndex = container.size() - 1;

    // Alternate between taking elements from the front and back
    bool isFront = true;

    while (frontIndex <= backIndex) {
        if (isFront) {
            arrangedElements.push_back(container.elements[frontIndex]);
            frontIndex++;
        } else {
            arrangedElements.push_back(container.elements[backIndex]);
            backIndex--;
        }

        isFront = !isFront;
    }

    // Update the container's elements with the arranged order
    container.elements = std::move(arrangedElements);

    // Update the iterator's indices
    this->frontIndex = 0;
    this->backIndex = container.size() - 1;
}


    MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer& container)
        : iterator_container(container), frontIndex(0), backIndex(0), isFront(true) {
            arrangeSideCross(iterator_container);
        }

    MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer& container, size_t frontIndex, size_t backIndex, bool isFront)
    : iterator_container(container), frontIndex(frontIndex), backIndex(backIndex), isFront(isFront) {}

    int MagicalContainer::SideCrossIterator::operator*() const {
        return isFront ? iterator_container.elements[frontIndex] : iterator_container.elements[backIndex];
    }

    MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator++() {
    if (isFront) {
        ++frontIndex;
        if (frontIndex > backIndex)
            frontIndex = backIndex;  // Make sure frontIndex doesn't go beyond backIndex
    } else {
        --backIndex;
        if (backIndex < frontIndex)
            backIndex = frontIndex;  // Make sure backIndex doesn't go beyond frontIndex
    }
    return *this;
}


    bool MagicalContainer::SideCrossIterator::operator==(const SideCrossIterator& other) const {
        // std::cout <<"front: "<< std::to_string(frontIndex);
        // std::cout <<" front other: "<< std::to_string(other.frontIndex) << std::endl;
        // std::cout <<"back: "<< std::to_string(backIndex);
        // std::cout <<" back other: "<< std::to_string(other.backIndex) << std::endl;
        // std::cout <<"isfront: "<< std::to_string(isFront);
        // std::cout <<" isfront other: "<< std::to_string(other.isFront) << std::endl;
        return (frontIndex == other.frontIndex) && (backIndex == other.backIndex);
    }

    bool MagicalContainer::SideCrossIterator::operator!=(const SideCrossIterator& other) const {
        return !(*this == other);
    }
   

    bool MagicalContainer::SideCrossIterator::operator>(const SideCrossIterator& other) const {
        return (frontIndex > other.frontIndex) || (backIndex < other.backIndex);
    }

    bool MagicalContainer::SideCrossIterator::operator<(const SideCrossIterator& other) const {
        return (frontIndex < other.frontIndex) || (backIndex > other.backIndex);
    }

    MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin() {
    return SideCrossIterator(iterator_container, 0, iterator_container.size() - 1, true);
}

MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end() const {
    return SideCrossIterator(iterator_container, iterator_container.size()-1, iterator_container.size() - 1, false);
}












    bool MagicalContainer::PrimeIterator::isPrime(int number) const {
        if (number < 2)
            return false;
        for (int i = 2; i <= std::sqrt(number); ++i) {
            if (number % i == 0)
                return false;
        }
        return true;
    }

    MagicalContainer::PrimeIterator::PrimeIterator(const MagicalContainer& container)
        : iterator_container(container), currentIndex(0) {}

    MagicalContainer::PrimeIterator::PrimeIterator(const MagicalContainer& container, size_t currentIndex)
        : iterator_container(container), currentIndex(currentIndex) {}

    int MagicalContainer::PrimeIterator::operator*() const {
        return iterator_container.elements[currentIndex];
    }

    MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator++() {
         ++currentIndex;
        while (currentIndex <= iterator_container.size()-1 && !isPrime(iterator_container.elements[currentIndex])){
            ++currentIndex;
        }
        return *this;
    }

    bool MagicalContainer::PrimeIterator::operator==(const PrimeIterator& other) const {
        // std::cout << "current: " << std::to_string(currentIndex) <<std::endl;
        // std::cout << "other current: " << std::to_string(other.currentIndex) <<std::endl;
        return currentIndex == other.currentIndex;
    }

    bool MagicalContainer::PrimeIterator::operator!=(const PrimeIterator& other) const {
        return !(*this == other);
    }

    bool MagicalContainer::PrimeIterator::operator>(const PrimeIterator& other) const {
        return currentIndex > other.currentIndex;
    }

    bool MagicalContainer::PrimeIterator::operator<(const PrimeIterator& other) const {
        return currentIndex < other.currentIndex;
    }

    MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin() {
        // std::cout << "begin: ";
        // std::cout << this << std::endl;
        size_t currentIndex = 0;
        while (currentIndex < iterator_container.size() && !isPrime(iterator_container.elements[currentIndex]))
            ++currentIndex;
        return PrimeIterator(iterator_container, currentIndex);
    }

    MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end() {
        // std::cout << "end: ";
        // std::cout << this << std::endl;
        return PrimeIterator(iterator_container, iterator_container.size());
    }
}
