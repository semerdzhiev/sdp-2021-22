#include <iostream>
#include <vector>
using namespace std;

template <class T>
class MinHeap {
    vector<T> heap;

    int parent(int i) {
        return (i-1)/2;
    }

    int left(int i) {
        return (2*i)+1;
    }

    int right(int i) {
        return (2*i)+2;
    }

    int minChild(int i) {
        if(size() <= left(i)) {
            return -1;
        }

        if(size() <= right(i)) {
            return left(i);
        }

        return (heap[left(i)] < heap[right(i)]) ? left(i) : right(i);
    }

    // recursive

    void sift_up(int startIndex) {
        if(startIndex < 0) {
            return;
        }

        if(heap[startIndex] < heap[parent(startIndex)]) {
            swap(heap[startIndex], heap[parent(startIndex)]);
            sift_up(parent(startIndex));
        }
    }

    void sift_down(int startIndex) {
        int currMinChild = minChild(startIndex);
        if(currMinChild == -1) {
            return;
        }

        if(heap[currMinChild] < heap[startIndex]) {
            swap(heap[currMinChild], heap[startIndex]);
            sift_down(currMinChild);
        }
    }

    // iterative

    /*void sift_up(int startIndex) {
        for(int movingIndex = startIndex; movingIndex > 0 && heap[movingIndex] < heap[parent(movingIndex)]; movingIndex = parent(movingIndex)) {
            swap(heap[movingIndex], heap[parent(movingIndex)]);
        }
    }

    void sift_down(int startIndex) {
        for(int movingIndex = minChild(startIndex); movingIndex != -1 && heap[movingIndex] < heap[parent(movingIndex)]; movingIndex = minChild(movingIndex)) {
            swap(heap[movingIndex], heap[parent(movingIndex)]);
        }
    }*/

public:

    int size() {
        return heap.size();
    }

    bool empty() {
        return heap.size() == 0;
    }

    void push(T newElement) {
        heap.push_back(newElement);
        sift_up(size()-1);
    }

    void print() {
        cout<< endl;
        for(int i = 0; i< heap.size(); ++i) {
            cout<< heap[i]<< " ";
        }
        cout<< endl;
    }

    void pop() {
        swap(heap[0], heap[size()-1]);
        heap.pop_back();
        sift_down(0);
    }

    T top() const {
        return heap[0];
    }
};
