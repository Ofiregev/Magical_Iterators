#ifndef MAGICAL_CONTAINER_HPP
#define MAGICAL_CONTAINER_HPP

#include <vector>

#include "AscendingIterator.hpp"
#include "PrimeIterator.hpp"
#include "SideCrossIterator.hpp"

class MagicalContainer {
    
private:
    std::vector<int> elements;
public:
    MagicalContainer();
    ~MagicalContainer();

    void addElement(int element);
    std::vector<int> getContainer();
    void removeElement(int element);
    int size() const;



};

#endif  // MAGICAL_CONTAINER_HPP
