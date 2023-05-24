#include "PrimeIterator.hpp"

PrimeIterator::PrimeIterator(MagicalContainer& container)
    : container(container), currentIndex(0) {}

PrimeIterator::PrimeIterator(const PrimeIterator& other)
    : container(other.container), currentIndex(other.currentIndex) {}

PrimeIterator::~PrimeIterator() {}

PrimeIterator& PrimeIterator::operator=(const PrimeIterator& other) {
    if (this != &other) {
        container = other.container;
        currentIndex = other.currentIndex;
    }
    return *this;
}

bool PrimeIterator::operator==(const PrimeIterator& other) const {
    return currentIndex == other.currentIndex;
}

bool PrimeIterator::operator!=(const PrimeIterator& other) const {
    return currentIndex != other.currentIndex;
}

bool PrimeIterator::operator>(const PrimeIterator& other) const {
    return currentIndex > other.currentIndex;
}

bool PrimeIterator::operator<(const PrimeIterator& other) const {
    return currentIndex < other.currentIndex;
}

// int& PrimeIterator::operator*() {
//     return container.getContainer()[currentIndex];
// }

PrimeIterator& PrimeIterator::operator++() {
    // Move to the next prime number
    ++currentIndex;
    while (currentIndex < container.size() && !isPrime(container.getContainer()[currentIndex]))
        ++currentIndex;
    return *this;
}

PrimeIterator PrimeIterator::begin() const {
    return PrimeIterator(container);
}

PrimeIterator PrimeIterator::end() const {
    PrimeIterator endIterator(container);
    endIterator.currentIndex = static_cast<size_t>(container.size());
    return endIterator;
}

bool PrimeIterator::isPrime(int num) {
    if (num < 2)
        return false;
    for (int i = 2; i * i <= num; ++i) {
        if (num % i == 0)
            return false;
    }
    return true;
}
