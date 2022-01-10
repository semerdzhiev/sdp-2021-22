#pragma once

#include "A.h"

class Set
{
    virtual void add(A number) = 0;
    virtual bool has(A number) = 0;

    virtual int hash(A element) = 0;

    virtual void print() = 0;
};