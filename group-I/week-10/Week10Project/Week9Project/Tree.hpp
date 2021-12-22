#pragma once

#include <vector>
#include <iostream>

using namespace std;

template<class T>
class Tree {
public:
	struct Node {
		T data;
		vector<Node*> children;

		Node(T data) : data(data) {}
	}*head;
private:
	void print(Node* head) {
		if (head->children.size() == 0) {
			cout << head->data<< " ";
			return;
		}

		for (int i = 0; i <= head->children.size() / 2; ++i) {
			print(head->children[i]);
		}
		cout << head->data<< " ";
		for (int i = head->children.size() / 2 + 1; i< head->children.size(); ++i) {
			print(head->children[i]);
		}
	}

	void clear(Node* head) {
		for (int i = 0; i < head->children.size(); ++i) {
			clear(head->children[i]);
		}
		delete head;
	}
public:
	void print() {
		print(head);
	}

	~Tree() {
		clear(head);
	}
};