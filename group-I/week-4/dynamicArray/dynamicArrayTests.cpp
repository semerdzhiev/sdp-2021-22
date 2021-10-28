#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "../catch.hpp"
#include "dynamicArray.hpp"

TEST_CASE("Pushing back one element to empty array", "[push_back]") {
    DynamicArray<int> da;
    da.push_back(1);
    REQUIRE(da[0] == 1);
}

TEST_CASE("Pushing back one element to array with one element", "[push_back]") {
    DynamicArray<int> da;
    da.push_back(1);
    da.push_back(5);
    REQUIRE(da[0] == 1);
    REQUIRE(da[1] == 5);
}

TEST_CASE("Pushing back 25 elements to empty array with capacity 5", "[push_back]") {
    DynamicArray<int> da(5);
    for (int index = 0; index < 25; ++index) {
        da.push_back(index*2 + 5);
    }
    REQUIRE(da[0] == 5);
    REQUIRE(da[17] == 39);
}

TEST_CASE("Inserting element to array with 10 elements", "[push_back]") {
    DynamicArray<int> da(10);
    for (int index = 0; index < 9; ++index) {
        da.push_back(index * 2 + 5);
    }
    da.insert(16, 4);
    REQUIRE(da[3] == 11);
    REQUIRE(da[4] == 16);
    REQUIRE(da[5] == 13);
    REQUIRE(da.size() == 10);
}

TEST_CASE("Erasing element to array with 10 elements", "[push_back]") {
    DynamicArray<int> da(10);
    for (int index = 0; index < 10; ++index) {
        da.push_back(index * 2 + 5);
    }
    da.erase(4);
    REQUIRE(da[3] == 11);
    REQUIRE(da[4] == 15);
    REQUIRE(da.size() == 9);
}