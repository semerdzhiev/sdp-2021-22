#pragma once
#include <list>
#include <vector>

#include "A.h"
#include "Set.h"

using namespace std;

class SeparateChainingHashSet: Set{
    const int volume;
    vector<list<A>> chains;

public:
    SeparateChainingHashSet(int volume = 10000);

    void add(A number);
    bool has(A number);
    int hash(A element);
    void print();
};