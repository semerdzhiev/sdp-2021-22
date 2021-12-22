#include <iostream>
#include "SeparateChainingHashSet.h"

using namespace std;

SeparateChainingHashSet::SeparateChainingHashSet(int volume): volume(volume) {
    chains.reserve(volume);
    for (int i = 0; i < volume; ++i) {
        chains.push_back(list<int>());
    }
}

void SeparateChainingHashSet::add(int number) {
    chains[number % volume].push_back(number);
}

bool SeparateChainingHashSet::has(int number) {
    for (list<int>::iterator it = chains[number % volume].begin(); it != chains[number % volume].end(); ++it) {
        if (*it == number) {
            return true;
        }
    }

    return false;
}

void SeparateChainingHashSet::print()
{
    for (int i = 0; i < volume; ++i) {
        for (list<int>::iterator it = chains[i].begin(); it != chains[i].end(); ++it) {
            cout << *it << " ";
        }
        cout << endl;
    }
}
