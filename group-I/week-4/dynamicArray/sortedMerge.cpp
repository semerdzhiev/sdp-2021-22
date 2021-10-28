#include <iostream>
#include <algorithm>
#include "../catch.hpp"
#include "dynamicArray.hpp"

using namespace std;

template<typename T>
DynamicArray<T> mergeSorted(int arr1[], int size1, int arr2[], int size2) {
    DynamicArray<T> result;
    for (int it1 = 0, it2 = 0; it1 < size1 || it2 < size2;) {
        if (it2 >= size2 || (it1 < size1 && arr1[it1] < arr2[it2])) {
            result.push_back(arr1[it1++]);
        }
        else {
            result.push_back(arr2[it2++]);
        }
    }

    return result;
}

TEST_CASE("Merging sorted arrays and checking results", "[mergeSorted]") {
    // ARRANGE
    int arr1[] = { 3, 15, 20, 187 };
    int arr2[] = { 1, 2, 16, 20, 93, 1234 };
    int expectedArr[] = { 1, 2, 3, 15, 16, 20, 20, 93, 187, 1234 };

    // ACT
    DynamicArray<int> da(mergeSorted<int>(arr1, 4, arr2, 6));

    // TEST
    for (int i = 0; i < 10; ++i) {
        REQUIRE(da[i] == expectedArr[i]);
    }
}