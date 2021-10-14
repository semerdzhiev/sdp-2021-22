#include <iostream>

using namespace std;

template <typename T>
void printArr(T* arr, int n) {
    for (int i = 0; i < n; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

template <class T>
class ConstantSizeArray {
    const int size;
    T data[5];

public:
    ConstantSizeArray(T data[5]) : size(5) {
        for (int i = 0; i < 5; ++i) {
            this->data[i] = data[i];
        }
    }

    void print() {
        printArr(data, size);
    }
};

template <class T>
class FixedSizeArray {
    const int size;
    T* data;

public:
    FixedSizeArray(T* data, int size) : size(size) {
        this->data = new T[size];
        for (int i = 0; i < size; ++i) {
            this->data[i] = data[i];
        }
    }

    ~FixedSizeArray() {
        delete[] data;
    }

    void print() {
        printArr(data, size);
    }
};

int main()
{
    int arr[] = { 1, 2, 3, 4, 5 };
    int n = 5;

    ConstantSizeArray<int> csa(arr);
    csa.print();

    FixedSizeArray<int> fsa(arr, n);
    fsa.print();

    return 0;
}