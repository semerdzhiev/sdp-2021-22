#include <iostream>
#include <vector>
#include <forward_list>
#include <stack>
using namespace std;

struct Node {
	int value;

	Node(int value) : value(value) {}
};
std::vector<Node> nodes;
std::vector<std::forward_list<int>> edges;


bool DFS(int startIndex, int endIndex) {
	std::vector<bool> visited(nodes.size());
	for (int i = 0; i < nodes.size(); ++i) {
		visited[i] = false;
	}
	std::stack<int> dfsStack;
	dfsStack.push(startIndex);
	visited[startIndex] = true;

	while (!dfsStack.empty()) {
		int newIndex = dfsStack.top();
		visited[newIndex] = true;
		dfsStack.pop();
		for (std::forward_list<int>::iterator it = edges[newIndex].begin(); it != edges[newIndex].end(); ++it) {
			if (*it == endIndex) {
				return true;
			}
			if (!visited[*it]) {
				dfsStack.push(*it);
			}
		}
	}
	return false;
}

int main() {
	for (int i = 0; i < 6; ++i) {
		nodes.push_back(Node(i));
		edges.push_back(std::forward_list<int>());
	}
	edges[0].push_front(1);
	edges[0].push_front(2);
	edges[1].push_front(2);
	edges[2].push_front(3);
	edges[2].push_front(4);
	edges[4].push_front(5);
	edges[5].push_front(2);


	cout << DFS(3, 0);


	return 0;
}