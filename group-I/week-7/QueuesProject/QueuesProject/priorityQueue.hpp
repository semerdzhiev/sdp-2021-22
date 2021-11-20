#include <iostream>
#include "dynamicArray.hpp"

template <class T>
class PriorityQueue {
	DynamicArray<T> data;

public:
	void enqueue(T element) {
		int insertionIndex = data.size();
		for (; data[insertionIndex-1] < element && insertionIndex > 0; --insertionIndex);
		data.insert(element, insertionIndex);
	}

	void dequeue() {
		data.pop_back();
	}

	T& front() {
		return data[data.size()-1];
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