#include <iostream>
#include "queue.hpp"
using namespace std;

int romanGeneral(int n) {
	Queue<int> q;
	for (int i = 0; i < n; ++i) {
		q.enqueue(i+1);
	}

	while (q.size() > 1) {
		q.enqueue(q.front());
		q.dequeue();
		q.dequeue();
	}

	return q.front();
}