#pragma once
#include <list>
#include <vector>

#include "Set.h"

using namespace std;

class SeparateChainingHashSet: Set{
    const int volume;
    vector<list<int>> chains;

public:
    SeparateChainingHashSet(int volume = 10000);

    void add(int number);
    bool has(int number);
    void print();
};