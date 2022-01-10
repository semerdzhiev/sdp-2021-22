#pragma once
#include <list>
#include <vector>
#include <utility>

#include "A.h"
#include "Map.h"

using namespace std;

class SeparateChainingHashMap : Map {
    const size_t volume;
    vector<list<pair<int, A>>> chains;

public:
    SeparateChainingHashMap(size_t volume = 10000);

    virtual void add(int key, A value);
    virtual bool hasKey(int key);

    virtual A& operator[](int key);

    virtual int hash(int key);

    virtual void print();
};