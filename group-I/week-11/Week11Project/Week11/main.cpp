#include <iostream>
#include "A.h"
#include "SeparateChainingHashSet.h"
#include "LinearProbingHashSet.h"
#include "SeparateChainingHashMap.h"
using namespace std;

int main() {
    SeparateChainingHashMap m(20);
    for (int i = 0; i < 10; i++)
    {
        m.add(i*i, A(1, i*4));
    }
    m.print();

    return 0;
}
