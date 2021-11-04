#include <iostream>
#include "stack.hpp"
#include "queue.hpp"

void reverse(DynamicArray<int>& arr);
bool balancedBrackets(string str);
bool differentBalancedBrackets(string str);

int romanGeneral(int n);

int main() {

	Stack<int> s;
	Queue<int> q;
	for (int i = 0; i < 10; ++i) {
		s.push(i);
		q.enqueue(i);
	}

	cout << "Stack test output: ";
	while (!s.empty()) {
		cout << s.top() << " ";
		s.pop();
	}
	cout << endl;

	cout << "Queue test output: ";
	while (!q.empty()) {
		cout << q.front() << " ";
		q.dequeue();
	}
	cout << endl;

	cout << "Reverse test output: ";
	DynamicArray<int> arr;
	for (int i = 0; i < 10; ++i) {
		arr.push_back(i*2);
	}
	reverse(arr);
	arr.print();

	cout << "Balanced brackets test output: "<< endl;
	string test1 = "((x+y)*z)";
	cout << test1 << " brackets are " << (balancedBrackets(test1) ? "" : "not ") << "balanced"<< endl;
	string test2 = "(x+y))((*z)";
	cout << test2 << " brackets are " << (balancedBrackets(test2) ? "" : "not ") << "balanced"<< endl;


	cout << "Different balanced brackets test output: " << endl;
	test1 = "{([x+y]*z)+{a+b-(d+c)}}";
	cout << test1 << " different brackets are " << (differentBalancedBrackets(test1) ? "" : "not ") << "balanced" << endl;
	test2 = "{(x+y})";
	cout << test2 << " different brackets are " << (differentBalancedBrackets(test2) ? "" : "not ") << "balanced" << endl;

	cout << "Roman general test output: " << endl;
	int n = 12;
	cout << "for " << n << " the answer is " << romanGeneral(n)<< endl;

	return 0;
}