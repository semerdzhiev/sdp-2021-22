#pragma once

#include <iostream>
#include "dynamicArray.hpp"

using namespace std;

template <class T>
class Stack {
	DynamicArray<T> data;

public:
	void push(T element) {
		data.push_back(element);
	}

	void pop() {
		data.erase(data.size() - 1);
	}

	T& top() {
		return data[data.size() - 1];
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