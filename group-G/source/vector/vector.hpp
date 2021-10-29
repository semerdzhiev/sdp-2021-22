#pragma once

#include "mem_inspect.hpp"

// if you comment out the next line, the tests will run on std::vector instead
// Make sure all tests pass on std::vector before trying to test your implementation
#define USER_VECTOR

/// Place your implementation below
/// The tests are testing not only interface but implementation details. For this to work allocation and deallocation happen in a specific way:
/// You must replace all new/delete with the following
/// T *ptr = new T[count]; -> NEW(T, count);
/// delete[] ptr; -> DELETE(ptr);

/// Example:

inline void test_allocation() {
	int *arr = NEW(int, 12);
	for (int c = 0; c < 12; c++) {
		arr[c] = c;
	}
	DELETE(arr);
}

#ifdef USER_VECTOR

template <typename T>
struct vector {
	// Implement me
};

#endif
