#pragma once

#include <iostream>
#include "doublyLinkedList.hpp"

using namespace std;

template <class T>
class Queue {
	DoublyLinkedList<T> data;

public:
	void enqueue(T element) {
		data.push_back(element);
	}

	void dequeue() {
		data.pop_front();
	}

	T& front() {
		return data.get_front();
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