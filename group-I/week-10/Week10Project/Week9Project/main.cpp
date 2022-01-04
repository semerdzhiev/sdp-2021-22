#include <iostream>
#include "binaryTree.hpp"
#include "dynamicArray.hpp"

template <class T>
void print(Node<T>* current) {
	if (current == NULL) {
		return;
	}

	cout << current->data << endl;
	print(current->left);
	print(current->right);
}

template <class T>
void print(BinaryTree<T> bt) {
	print(bt.head);
}

template <class T>
Node<T>* treeFromSortedArray(DynamicArray<T>& da, int left, int right) {
	if (left == right) {
		return nullptr;
	}

	int mid = (left + right) / 2;
	return new Node<T>(da[mid],
		treeFromSortedArray(da, left, mid),
		treeFromSortedArray(da, mid + 1, right));
}

template <class T>
BinaryTree<T> treeFromSortedArray(DynamicArray<T>& da) {
	BinaryTree<T> bt;
	bt.head = treeFromSortedArray(da, 0, da.size());
	return bt;
}

int main() {
	/*BinaryTree<int> bt;
	bt.head = new Node<int>(5, nullptr, nullptr);
	bt.head->left = new Node<int>(2, nullptr, nullptr);
	bt.head->left->left = new Node<int>(17, nullptr, nullptr);
	bt.head->right = new Node<int>(8, nullptr, nullptr);
	print(bt);*/
	DynamicArray<int> da;
	for (int i = 0; i < 10; ++i) {
		da.push_back(i);
	}

	BinaryTree<int> bt = treeFromSortedArray(da);
	print(bt);


	return 0;
}