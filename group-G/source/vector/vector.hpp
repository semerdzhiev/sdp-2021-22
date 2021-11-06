#pragma once

#include "mem_inspect.hpp"
#include "type_traits.hpp"

#include <stdexcept>

#define USER_VECTOR

template <typename T>
struct vector {
private:
	T *data = nullptr;
	int count = 0;
	int cap = 0;

	void setSize(int newCap) {
		if (newCap == cap) {
			return;
		}
		T *newData = NEW(T, newCap);
		try {
			for (int c = 0; c < std::min(count, newCap); c++) {
				newData[c] = data[c];
			}
		} catch (...) {
			delete[] newData;
			throw;
		}

		DELETE(data);
		data = newData;
		cap = newCap;
	}

	void checkResize() {
		if (count == cap) {
			const int newCap = cap ? cap * 2 : 1;
			setSize(newCap);
		}
	}
public:
	/// Direction specifier for iterators, used to remove duplicating code for forward/backward iterator
	enum IteratorDirection {
		ForwardIterator = 1, // begins at index 0, ends in (size() + 1)
		BackwardIterator = -1 // begins at index (size() - 1), ends in index -1
	};

	/// Iterator template, can produce forward/backward iterator and const/non const
	/// @tparam direction - specifies which direction does incrementing move the iterator
	///                     direction's value is either 1 or -1, used directly for increment/decrement
	/// @tparam Type - either T or const T, to enable/disable the correct access to values
	///                if T - enables T &operator*() / T *operator->
	///                if const T - enables const T &operator*() const / const T *operator->() const
	template <IteratorDirection direction = ForwardIterator, typename Type = T>
	struct iterator_base {
	private:
		Type *ptr = nullptr;

		// only constructable from the vector itself
		iterator_base(T *ptr)
			: ptr(ptr)
		{}
		friend struct vector;
	public:
		/// Reference access for const_*_iterator
		template <typename Q = Type>
		const typename enable_if<is_const<Q>::value, Q>::type &operator*() const {
			return *ptr;
		}

		/// Reference access for *_iterator
		template <typename Q = Type>
		typename enable_if<!is_const<Q>::value, Q>::type &operator*() {
			return *ptr;
		}

		/// Pointer access for const_*_iterator
		template <typename Q = Type>
		const typename enable_if<is_const<Q>::value, Q>::type *operator->() const {
			return ptr;
		}

		/// Pointer access for *_iterator
		template <typename Q = Type>
		typename enable_if<!is_const<Q>::value, Q>::type *operator->() {
			return ptr;
		}

		iterator_base &operator++() {
			ptr += int(direction);
			return *this;
		}

		iterator_base operator++(int) {
			iterator copy(*this);
			ptr += int(direction);
			return copy;
		}

		iterator_base &operator--() {
			ptr -= int(direction);
			return *this;
		}

		iterator_base operator--(int) {
			iterator_base copy(*this);
			ptr -= int(direction);
			return copy;
		}

		/// Signed difference between two iterators (maybe negative)
		int operator-(const iterator_base &other) const {
			return int(ptr - other.ptr);
		}

		/// Positive offset in direction of the iterator
		iterator_base operator+(int offset) const {
			return iterator_base(ptr + offset * int(direction));
		}

		/// Negative offset in direction of the iterator
		iterator_base operator-(int offset) const {
			return iterator_base(ptr - offset * int(direction));
		}

		/// Equality comparison, allows comparing different types of iterators
		template <IteratorDirection OtherDir, typename OtherType>
		bool operator==(const iterator_base<OtherDir, OtherType> &other) const {
			return ptr == other.ptr;
		}

		/// Inequality comparison, allows comparing different types of iterators
		template <IteratorDirection OtherDir, typename OtherType>
		bool operator!=(const iterator_base<OtherDir, OtherType> &other) const {
			return !(*this == other);
		}

		/// Order comparison, allows comparing different types of iterators
		bool operator<(const iterator_base &other) const {
			if (direction == IteratorDirection::ForwardIterator) {
				return ptr < other.ptr;
			} else {
				return ptr > other.ptr;
			}
		}
	};

	typedef iterator_base<IteratorDirection::ForwardIterator, T> iterator;
	typedef iterator_base<IteratorDirection::ForwardIterator, const T> const_iterator;

	typedef iterator_base<IteratorDirection::BackwardIterator, T> reverse_iterator;
	typedef iterator_base<IteratorDirection::BackwardIterator, const T> const_reverse_iterator;

	const_iterator cbegin() const {
		return const_iterator(data);
	}

	const_iterator cend() const {
		return const_iterator(data + count);
	}

	const_iterator begin() const {
		return const_iterator(data);
	}

	const_iterator end() const {
		return const_iterator(data + count);
	}

	iterator begin() {
		return iterator(data);
	}

	iterator end() {
		return iterator(data + count);
	}

	reverse_iterator rbegin() {
		return reverse_iterator(data + count - 1);
	}

	reverse_iterator rend() {
		return reverse_iterator(data - 1);
	}

	const_reverse_iterator rbegin() const {
		return const_reverse_iterator(data + count - 1);
	}

	const_reverse_iterator rend() const {
		return const_reverse_iterator(data - 1);
	}

	const_reverse_iterator crbegin() const {
		return const_reverse_iterator(data + count - 1);
	}

	const_reverse_iterator crend() const {
		return const_reverse_iterator(data - 1);
	}

	vector() = default;

	vector(int size)
		: data(NEW(T, size))
		, count(size)
		, cap(size) {
	}

	vector(int size, const T &value)
		: data(NEW(T, size))
		, count(size)
		, cap(size) {
		for (int c = 0; c < size; c++) {
			data[c] = value;
		}
	}

	/// Move constructor, leaves RHS in empty state
	vector(vector &&other) {
		std::swap(data, other.data);
		std::swap(count, other.count);
		std::swap(cap, other.cap);
	}

	/// Move assignment, leaves RHS in empty state
	vector &operator=(vector &&other) {
		if (this == &other) {
			return *this;
		}

		std::swap(data, other.data);
		std::swap(count, other.count);
		std::swap(cap, other.cap);
		other.clear();

		return *this;
	}

	vector(const vector &other) {
		setSize(other.count);
		count = other.count;
		for (int c = 0; c < count; c++) {
			data[c] = other.data[c];
		}
	}

	vector &operator=(const vector &other) {
		if (this == &other) {
			return *this;
		}

		if (other.count > cap) {
			setSize(other.count);
		}
		count = other.count;
		for (int c = 0; c < count; c++) {
			data[c] = other.data[c];
		}

		return *this;
	}

	~vector() {
		DELETE(data);
	}

	void push_back(const T &value) {
		checkResize();
		data[count] = value;
		++count;
	}

	int size() const {
		return count;
	}

	bool empty() const {
		return size() == 0;
	}

	void pop_back() {
		--count;
	}

	T &front() {
		return data[0];
	}

	T &back() {
		return data[count - 1];
	}

	T &operator[](int c) {
		return data[c];
	}

	const T &operator[](int c) const {
		return data[c];
	}

	T &at(int c) {
		if (c < 0 || c >= count) {
			throw std::out_of_range("vector index out of range");
		}
		return data[c];
	}

	const T &at(int c) const {
		if (c < 0 || c >= count) {
			throw std::out_of_range("vector index out of range");
		}
		return data[c];
	}

	int capacity() const {
		return cap;
	}

	void resize(int newSize) {
		if (newSize > cap) {
			setSize(newSize);
		}
		count = newSize;
	}

	void resize(int newSize, const T &value) {
		if (newSize > count) {
			if (newSize > cap) {
				setSize(newSize);
			}
			for (int c = count; c < newSize; c++) {
				data[c] = value;
			}
		}
		count = newSize;
	}

	void clear() {
		count = 0;
	}

	void reserve(int requested) {
		if (requested > cap) {
			setSize(requested);
		}
	}

	void shrink_to_fit() {
		setSize(count);
	}

	/// Insert new element so that its index is at given position
	void insert(iterator pos, const T &value) {
		// must convert to index, iterator may be invalidated if there is not enough capacity
		const int index = pos - begin();
		checkResize();
		pos = iterator(begin() + index);

		// shift all elements 1 position
		for (iterator it = end(); it != pos; --it) {
			*it = *(it - 1);
		}
		*pos = value;
		++count;
	}

	/// Erase element at given position
	void erase(const iterator &pos) {
		erase(pos, pos + 1);
	}

	/// Erase a range of elements [from, to)
	void erase(const iterator &from, const iterator &to) {
		const int eraseCount = to - from;

		for (iterator it = to; it != end(); ++it) {
			*(it - eraseCount) = *it;
		}

		count -= eraseCount;
	}
};
