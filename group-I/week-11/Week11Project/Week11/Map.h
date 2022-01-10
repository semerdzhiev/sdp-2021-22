#pragma once

#include "A.h"

class Map
{
    virtual void add(int key, A value) = 0;
    virtual bool hasKey(int key) = 0;

    virtual A& operator[](int key) = 0;

    virtual int hash(int key) = 0;

    virtual void print() = 0;
};