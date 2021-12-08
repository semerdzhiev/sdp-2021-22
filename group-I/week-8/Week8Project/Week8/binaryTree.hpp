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