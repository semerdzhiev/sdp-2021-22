#include <iostream>
#include "linkedList.hpp"
#include "doublyLinkedList.hpp"
#include "queue.hpp"
#include <iostream>
#include "dynamicArray.hpp"

DynamicArray<int> mergeKSorted(DynamicArray<DynamicArray<int>> sortedArrays);

int main() {


	int K;
	DynamicArray<DynamicArray<int>> input;
	cin >> K;

	int n;
	int element;
	for (int arrayIndex = 0; arrayIndex < K; ++arrayIndex) {
		input.push_back(DynamicArray<int>());
		cin >> n;
		for (int elementIndex = 0; elementIndex < n; ++elementIndex) {
			cin >> element;
			input[arrayIndex].push_back(element);
		}
	}
	mergeKSorted(input).print();


	LinkedList<int> l;
	for (int i = 0; i < 10; ++i) {
		l.push_front(i);
	}
	l.print();

	DoublyLinkedList<int> dl;
	for (int i = 0; i < 10; ++i) {
		dl.push_front(i);
	}
	dl.reversePrint();

	Queue<int> q;
	for (int i = 0; i < 10; ++i) {
		q.enqueue(i);
	}
	while (q.size() > 0) {
		cout << q.front() << " ";
		q.dequeue();
	}
	cout << endl;

	return 0;
}