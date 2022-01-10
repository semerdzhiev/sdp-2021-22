#include <iostream>
#include <exception>

#include "SeparateChainingHashMap.h"

using namespace std;

SeparateChainingHashMap::SeparateChainingHashMap(size_t volume): volume(volume)
{
	chains.reserve(volume);
	for (int i = 0; i < volume; ++i) {
		chains.push_back(list<pair<int, A>>());
	}
}

void SeparateChainingHashMap::add(int key, A value)
{
	chains[hash(key)].push_back(make_pair(key, value));
}

bool SeparateChainingHashMap::hasKey(int key)
{
	for (list<pair<int, A>>::iterator it = chains[hash(key)].begin(); it != chains[hash(key)].end(); ++it) {
		if (it->first == key) {
			return true;
		}
	}

	return false;
}

A& SeparateChainingHashMap::operator[](int key)
{
	for (list<pair<int, A>>::iterator it = chains[hash(key)].begin(); it != chains[hash(key)].end(); ++it) {
		if (it->first == key) {
			return it->second;
		}
	}

	throw std::exception();
}

int SeparateChainingHashMap::hash(int key)
{
	std::hash<int> hasher;
	return hasher(key) % volume;
}

void SeparateChainingHashMap::print()
{
	for (int i = 0; i < volume; ++i) {
		for (list<pair<int, A>>::iterator it = chains[i].begin(); it != chains[i].end(); ++it) {
			cout << "(" << it->first << ", " << "(" << it->second.a<< ", "<< it->second.b << ")" << ")" << " ";
		}
		cout << endl;
	}
}
