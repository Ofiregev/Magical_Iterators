#include "SideCrossIterator.hpp"
#include "MagicalContainer.hpp"

SideCrossIterator::SideCrossIterator(MagicalContainer& container)
    : container(container), currentIndex(0) {}

SideCrossIterator::SideCrossIterator(const SideCrossIterator& other)
    : container(other.container), currentIndex(other.currentIndex) {}

SideCrossIterator::~SideCrossIterator() {}

SideCrossIterator& SideCrossIterator::operator=(const SideCrossIterator& other) {
    if (this != &other) {
        container = other.container;
        currentIndex = other.currentIndex;
    }
    return *this;
}

bool SideCrossIterator::operator==(const SideCrossIterator& other) const {
    return currentIndex == other.currentIndex;
}

bool SideCrossIterator::operator!=(const SideCrossIterator& other) const {
    return currentIndex != other.currentIndex;
}

bool SideCrossIterator::operator>(const SideCrossIterator& other) const {
    return currentIndex > other.currentIndex;
}

bool SideCrossIterator::operator<(const SideCrossIterator& other) const {
    return currentIndex < other.currentIndex;
}

// int& SideCrossIterator::operator*() {
//     std::vector<int>& containerElements = container.getContainer();
//     return containerElements[currentIndex];
// }

SideCrossIterator& SideCrossIterator::operator++() {
    // Move to the next element in the side-cross order
    if (currentIndex % 2 == 0) {
        currentIndex += 2;
        if (currentIndex >= container.size())
            currentIndex = 1;
    } else {
        currentIndex -= 2;
        if (currentIndex < 0)
            currentIndex = static_cast<size_t>(container.size()) - 2;
    }
    return *this;
}

SideCrossIterator SideCrossIterator::begin() const {
    return SideCrossIterator(container);
}

SideCrossIterator SideCrossIterator::end() const {
    SideCrossIterator endIterator(container);
    endIterator.currentIndex = static_cast<size_t>(container.size());
    return endIterator;
}

