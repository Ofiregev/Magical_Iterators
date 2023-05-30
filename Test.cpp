#include "doctest.h"
#include "MagicalContainer.hpp"
#include <chrono>
#include <iostream>

using namespace ariel;
using namespace std;

TEST_SUITE("Test 1 - initialazing container") {
    MagicalContainer mc;
    TEST_CASE("Creating container and push elements"){
        
        int i = 1;
        while (i<=10)
        {
            mc.addElement(i);
            CHECK(mc.size() == i);
            i++;
        }
        
    }
    TEST_CASE("Removing elements from container"){
        size_t current_size = 10;
        int i = 1;
        while (i<=10)
        {
            if (i%2 == 1){
            mc.removeElement(i);
            i++;
        }
        i++;
        }
        current_size = current_size / 2;
        CHECK(mc.size() == current_size);                                
    }TEST_CASE("Removing elements from empty container"){
        MagicalContainer mc2;
        mc2.addElement(1);
        mc2.addElement(2);
        mc2.removeElement(1);
        mc2.removeElement(2);
        CHECK_THROWS(mc2.removeElement(1));
}
TEST_SUITE("Test 2 - Check Iterators") {
    TEST_CASE("Ascending"){
    MagicalContainer mc;
    int i = 1;
    while (i<=10)
        {
            mc.addElement(i);
            CHECK(mc.size() == i);
            i++;
        }
    MagicalContainer::AscendingIterator ascIter(mc);
    i = 1;
    for (auto it = ascIter.begin(); it != ascIter.end(); ++it) {
        CHECK((*it) == i);
        i++;
    }
    MagicalContainer mc2;
    mc2.addElement(15);
    mc2.addElement(3);
    mc2.addElement(20);
    mc2.addElement(10);
    mc2.addElement(5);
    MagicalContainer::AscendingIterator ascIter2(mc2);
    auto it = ascIter2.begin();
    CHECK(*it == 3);
    ++it;
    CHECK(*it == 5);
    }
      
    TEST_CASE("Cross"){
    MagicalContainer mc;
    mc.addElement(15);
    mc.addElement(3);
    mc.addElement(20);
    mc.addElement(10);
    mc.addElement(5);
    MagicalContainer::SideCrossIterator crossIter(mc);
    auto it = crossIter.begin();
    CHECK(*it == 15);
    ++it;
    CHECK(*it == 5);
    ++it;
    CHECK(*it == 3);
    ++it;
    CHECK(*it == 10);
    ++it;
    CHECK(*it == 20);
    mc.removeElement(10);
    CHECK(mc.size() == 4);
    }
    TEST_CASE("Prime"){
    MagicalContainer mc;
    mc.addElement(15);
    mc.addElement(3);
    mc.addElement(20);
    mc.addElement(10);
    mc.addElement(5);
    mc.addElement(13);
    MagicalContainer::PrimeIterator primeIter(mc);
    auto it = primeIter.begin();
    CHECK(*it == 3);
    ++it;
    CHECK(*it == 5);
    ++it;
    CHECK(*it == 13);
    mc.addElement(11);
    ++it;
    CHECK(*it == 11);
    }
}
}