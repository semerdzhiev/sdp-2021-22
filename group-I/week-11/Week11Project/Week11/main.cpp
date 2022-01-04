#include <iostream>
#include "SeparateChainingHashSet.h"
#include "LinearProbingHashSet.h"
using namespace std;

int main() {
    LinearProbingHashSet h(131);
    for (int i = 0; i < 260; i+=2)
    {
        h.add(i);
    }
    h.print();

    return 0;
}
