#pragma once

#include <iostream>
#include <vector>

#include "Set.h"

using namespace std;

class LinearProbingHashSet : Set {
    int volume;
    int remainingFree;

    vector<bool> takenPositions;
    vector<int> data;

    void rehash();
public:
    LinearProbingHashSet(int volume = 10000);

    void add(int number);
    bool has(int number);
    void print();
};

