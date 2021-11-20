#include <iostream>
#include "dynamicArray.hpp"
#include "stack.hpp"
using namespace std;

void reverse(DynamicArray<int>& arr) {
	Stack<int> s;

	for (int i = 0; i < arr.size(); ++i) {
		s.push(arr[i]);
	}

	for (int i = 0; i < arr.size(); ++i) {
		arr[i] = s.top();
		s.pop();
	}
}