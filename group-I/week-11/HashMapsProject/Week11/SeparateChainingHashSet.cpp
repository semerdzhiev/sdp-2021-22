#include <iostream>
#include <functional>
#include "A.h"
#include "SeparateChainingHashSet.h"

using namespace std;

SeparateChainingHashSet::SeparateChainingHashSet(int volume): volume(volume) {
    chains.reserve(volume);
    for (int i = 0; i < volume; ++i) {
        chains.push_back(list<A>());
    }
}

void SeparateChainingHashSet::add(A number) {
    chains[hash(number)].push_back(number);
}

bool SeparateChainingHashSet::has(A number) {
    for (list<A>::iterator it = chains[hash(number)].begin(); it != chains[hash(number)].end(); ++it) {
        if (*it == number) {
            return true;
        }
    }

    return false;
}

int SeparateChainingHashSet::hash(A element) {
    //return (element.a + element.b) % volume;
    std::hash<A> hasher;
    return hasher(element) % volume;
}

void SeparateChainingHashSet::print()
{
    for (int i = 0; i < volume; ++i) {
        for (list<A>::iterator it = chains[i].begin(); it != chains[i].end(); ++it) {
            cout << "("<< it->a<< ", "<< it->b<< ")" << " ";
        }
        cout << endl;
    }
}
