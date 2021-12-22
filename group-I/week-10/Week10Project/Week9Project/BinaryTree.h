#pragma once

#include <iostream>

using namespace std;

template<class T>
struct Node {
	T data;
	Node* left;
	Node* right;

	Node(T data, Node* left, Node* right) : data(data), left(left), right(right) {}
};

template<class T>
class BinaryTree {
public:

	Node<T>* head;
};

template<class T>
bool isBST(Node<T>* head, T* lower = nullptr, T* upper = nullptr) {
	if (head == nullptr) {
		return true;
	}

	if ((lower != nullptr && head->data < *lower) || (upper != nullptr && head->data > *upper)) {
		return false;
	}

	return isBST(head->left, lower, &(head->data)) && isBST(head->right, &(head->data), upper);
}