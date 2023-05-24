#include "AscendingIterator.hpp"

AscendingIterator::AscendingIterator(MagicalContainer& container)
    : container(container), currentIndex(0) {}

AscendingIterator::AscendingIterator(const AscendingIterator& other)
    : container(other.container), currentIndex(other.currentIndex) {}

AscendingIterator::~AscendingIterator() {}

AscendingIterator& AscendingIterator::operator=(const AscendingIterator& other) {
    if (this != &other) {
        container = other.container;
        currentIndex = other.currentIndex;
    }
    return *this;
}

bool AscendingIterator::operator==(const AscendingIterator& other) const {
    return currentIndex == other.currentIndex;
}

bool AscendingIterator::operator!=(const AscendingIterator& other) const {
    return currentIndex != other.currentIndex;
}

bool AscendingIterator::operator>(const AscendingIterator& other) const {
    return currentIndex > other.currentIndex;
}

bool AscendingIterator::operator<(const AscendingIterator& other) const {
    return currentIndex < other.currentIndex;
}

// int& AscendingIterator::operator*() {
//     std::vector<int>& containerElements = container.getContainer();
//     size_t index = static_cast<size_t>(currentIndex);
//     return containerElements[index];

// }


AscendingIterator& AscendingIterator::operator++() {
    ++currentIndex;
    return *this;
}

AscendingIterator AscendingIterator::begin() const {
    return AscendingIterator(container);
}

AscendingIterator AscendingIterator::end() const {
    AscendingIterator endIterator(container);
    endIterator.currentIndex = static_cast<size_t>(container.size());
    return endIterator;
}
