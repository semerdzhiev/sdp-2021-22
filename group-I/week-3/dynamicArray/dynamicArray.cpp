#include <iostream>

using namespace std;

template <class T>
class DynamicArray {
    const int startSize;
    const int expansionFactor = 2;

    int size;
    int capacity;
    T* data;

    void expand() {
        capacity *= expansionFactor;
        T* newData = new T[capacity];
        for (int copiedElementIndex = 0; copiedElementIndex < size; ++copiedElementIndex) {
            newData[copiedElementIndex] = data[copiedElementIndex];
        }
        delete[] data;

        data = newData;
    }

public:
    DynamicArray(size_t startSize = 10) : startSize(startSize) {
        size = 0;
        capacity = (startSize == 0) ? 10 : startSize;
        data = new int[capacity];
    }

    ~DynamicArray() {
        delete[] data;
    }

    void push_back(T newValue) {
        if (size == capacity) {
            expand();
        }
        data[size++] = newValue;
    }

    void insert(T newValue, size_t position) {
        if (size == capacity) {
            expand();
        }

        for (int movedElementIndex = size - 1; movedElementIndex > position; --movedElementIndex) {
            data[movedElementIndex + 1] = data[movedElementIndex];
        }
        ++size;
    }

    void erase(int position) {
        for (int movedElementIndex = position; movedElementIndex < size - 1; ++movedElementIndex) {
            data[movedElementIndex] = data[movedElementIndex + 1];
        }
        --size;
    }

    void print() {
        for (int i = 0; i < size; ++i) {
            cout << data[i] << " ";
        }
        cout << endl;
    }
};

int main()
{
    DynamicArray<int> da(5);
    da.push_back(5);
    da.push_back(6);
    da.push_back(7);
    da.push_back(8);
    da.erase(2);
    da.print();

    return 0;
}