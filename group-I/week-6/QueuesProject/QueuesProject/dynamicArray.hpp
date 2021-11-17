#pragma once

#include <iostream>

using namespace std;

template <class T>
class DynamicArray {
    const int startSize;
    const int expansionFactor = 2;

    int size_;
    int capacity;
    T* data;

    void expand() {
        capacity *= expansionFactor;
        T* newData = new T[capacity];
        for (int copiedElementIndex = 0; copiedElementIndex < size_; ++copiedElementIndex) {
            newData[copiedElementIndex] = data[copiedElementIndex];
        }
        delete[] data;

        data = newData;
    }

    void clear() {
        delete[] data;
        data = nullptr;
        size_ = 0;
    }

    void copy(const DynamicArray<T>& other) {
        clear();
        capacity = other.capacity;
        size_ = other.size_;
        data = new T[size_];
        for (int i = 0; i < size_; ++i) {
            data[i] = other.data[i];
        }
    }

public:
    DynamicArray(size_t startSize = 10) : startSize(startSize) {
        size_ = 0;
        capacity = (startSize == 0) ? 10 : startSize;
        data = new T[capacity];
    }

    DynamicArray(const DynamicArray<T>& other): startSize(10) {
        copy(other);
    }

    void operator=(const DynamicArray<T>& other) {
        if (this != &other) {
            copy(other);
        }
        return *this;
    }

    ~DynamicArray() {
        clear();
    }

    void push_back(T newValue) {
        if (size_ == capacity) {
            expand();
        }
        data[size_++] = newValue;
    }

    void pop_back() {
        size_--;
    }

    T& operator[](int index) {
        return data[index];
    }

    void insert(T newValue, size_t position) {
        if (size_ == capacity) {
            expand();
        }

        for (int movedElementIndex = size_ - 1; movedElementIndex > position-1; --movedElementIndex) {
            data[movedElementIndex + 1] = data[movedElementIndex];
        }
        data[position] = newValue;
        ++size_;
    }

    void erase(int position) {
        for (int movedElementIndex = position; movedElementIndex < size_ - 1; ++movedElementIndex) {
            data[movedElementIndex] = data[movedElementIndex + 1];
        }
        --size_;
    }

    int size() {
        return size_;
    }

    void print() {
        for (int i = 0; i < size_; ++i) {
            cout << data[i] << " ";
        }
        cout << endl;
    }
};