#pragma once

#include <iostream>

using namespace std;

template<class T>
class LinkedList {
	struct Node {
		T data;
		Node* next;

		Node(T data, Node* next) : data(data), next(next) {}
	};

	Node* head;

	void clear(Node* node) {
		if (node == nullptr) {
			return;
		}

		clear(node->next);
		delete node;
	}

	void clear() {
		clear(head);
		head = nullptr;
	}

	Node* copy(const Node* node) {
		if (node == nullptr) {
			return nullptr;
		}

		return new Node(node->data, copy(node->next));
	}

	void copy(const LinkedList& other) {
		clear();
		head = copy(head);
	}

public:

	LinkedList() : head(nullptr) {}
	LinkedList(const LinkedList& other) {
		copy(other);
	}
	LinkedList& operator=(const LinkedList& other) {
		if (this != &other) {
			copy(other);
		}

		return *this;
	}
	~LinkedList() {
		clear();
	}

	void push_front(T newElement) {
		head = new Node(newElement, head);
	}

	void pop_front() {
		if (head == nullptr) {
			return;
		}

		Node* oldHead = head;
		head = head->next;
		delete oldHead;
	}

	void print(Node* node) {
		if (node == nullptr) {
			return;
		}

		cout << node->data << " ";
		print(node->next);
	}

	void print() {
		print(head);
		cout << endl;
	}
};