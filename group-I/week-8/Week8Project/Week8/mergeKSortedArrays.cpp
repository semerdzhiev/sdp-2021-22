#include <iostream>
#include "priorityQueue.hpp"

DynamicArray<int> mergeKSorted(DynamicArray<DynamicArray<int>> sortedArrays) {
    PriorityQueue<int> pq;

    bool indexExistsForAtleastOneArray = true;
    for (size_t insertionIndex = 0; indexExistsForAtleastOneArray; ++insertionIndex) {
        indexExistsForAtleastOneArray = false;
        for (size_t arrayIndex = 0; arrayIndex < sortedArrays.size(); ++arrayIndex) {
            if (sortedArrays[arrayIndex].size() > insertionIndex) {
                pq.print();
                pq.enqueue(sortedArrays[arrayIndex][insertionIndex]);
                indexExistsForAtleastOneArray = true;
            }
        }
    }

    DynamicArray<int> result;
    while (!pq.empty()) {
        result.push_back(pq.front());
        pq.dequeue();
    }
    return result;
};