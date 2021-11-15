#pragma once

#include <cassert>
#include "mem_inspect.hpp"

// Uncomment to test this list
// #define USER_LIST

// use NEW(Type, count) for allocation
// use DELETE(ptr) for deallocation

// Uncomment if you allocate dynamic dummy node, example: this->dummy = NEW(Node, 1)
// #define LIST_EXTRA_ELEMENT

template <typename T>
struct list {
	struct Node {
		Node *next = nullptr;
		Node *prev = nullptr;
		T data;
	};
private:
public:
};