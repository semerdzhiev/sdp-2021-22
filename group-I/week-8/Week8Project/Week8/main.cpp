#include <iostream>
#include "binaryTree.hpp"

template <class T>
void print(Node<T> * current) {
	if (current == NULL) {
		return;
	}

	print(current->left);
	cout << current->data << endl;
	print(current->right);
}

template <class T>
void print(BinaryTree<T> bt) {
	print(bt.head);
}

int main() {
	BinaryTree<int> bt;
	bt.head = new Node<int>(5, nullptr, nullptr);
	bt.head->left = new Node<int>(2, nullptr, nullptr);
	bt.head->left->left = new Node<int>(17, nullptr, nullptr);
	bt.head->right = new Node<int>(8, nullptr, nullptr);
	print(bt);

	return 0;
}