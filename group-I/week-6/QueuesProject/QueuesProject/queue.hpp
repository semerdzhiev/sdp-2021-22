#pragma once

#include <iostream>
#include "dynamicArray.hpp"

using namespace std;

template <class T>
class Queue {
	DynamicArray<T> data;

public:
	void enqueue(T element) {
		data.push_back(element);
	}

	void dequeue() {
		data.erase(0);
	}

	T& front() {
		return data[0];
	}

	int size() {
		return data.size();
	}

	bool empty() {
		return size() == 0;
	}

	void print() {
		data.print();
	}
};