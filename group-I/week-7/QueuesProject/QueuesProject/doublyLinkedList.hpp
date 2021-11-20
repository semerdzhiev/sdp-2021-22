#pragma once

#include <iostream>

using namespace std;

template<class T>
class DoublyLinkedList {
	struct Node {
		T data;
		Node* prev;
		Node* next;

		Node(T data, Node* prev, Node* next) : data(data), prev(prev), next(next) {}
	};

	Node* head;
	Node* tail;

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

	Node* copy(const Node* node, const Node* prevNode) {
		if (node == nullptr) {
			return nullptr;
		}

		Node* currentNode = new Node(node->data, prevNode, nullptr);
		currentNode->next = copy(node->next, currentNode);
		return currentNode;
	}

	void copy(const DoublyLinkedList& other) {
		clear();
		head = copy(head, nullptr);
	}

public:

	DoublyLinkedList() : head(nullptr), tail(nullptr) {}
	DoublyLinkedList(const DoublyLinkedList& other) {
		copy(other);
	}
	DoublyLinkedList& operator=(const DoublyLinkedList& other) {
		if (this != &other) {
			copy(other);
		}

		return *this;
	}
	~DoublyLinkedList() {
		clear();
	}

	void push_front(T newElement) {
		head = new Node(newElement, nullptr, head);
		if (head->next != nullptr) {
			head->next->prev = head;
		}
		else {
			tail = head;
		}
	}

	void pop_front() {
		if (head == nullptr) {
			return;
		}
		
		Node* oldHead = head;
		head = head->next;
		delete oldHead;

		if (head == nullptr || head->next == nullptr) {
			tail = head;
		}
	}

	void push_back(T newElement) {
		tail = new Node(newElement, tail, nullptr);
		if (tail->prev != nullptr) {
			tail->prev->next = tail;
		}
		else {
			head = tail;
		}
	}

	void pop_back() {
		if (tail == nullptr) {
			return;
		}

		Node* oldTail = tail;
		tail = tail->prev;
		delete oldTail;

		if (tail == nullptr || tail->prev == nullptr) {
			head = tail;
		}
	}

	T& get_back() {
		return tail->data;
	}

	T& get_front() {
		return head->data;
	}

	int size(Node* node) {
		if (node == nullptr) {
			return 0;
		}

		return 1 + size(node->next);
	}

	int size() {
		return size(head);
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

	void reversePrint(Node* node) {
		if (node == nullptr) {
			return;
		}

		cout << node->data << " ";
		reversePrint(node->prev);
	}

	void reversePrint() {
		reversePrint(tail);
		cout << endl;
	}
};