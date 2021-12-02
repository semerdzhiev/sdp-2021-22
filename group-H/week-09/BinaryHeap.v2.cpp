#include <iostream>
using namespace std;
class BinaryHeap {
    int array[100];
    int currentEl;

    int getParentPos(int ind) {
        return (ind-1) / 2;
    }
public:
    BinaryHeap(): currentEl(0) {};
    void add(int key) {
        // Make validation for the size or make it dynamic
        array[currentEl] = key;
        int parent = getParentPos(currentEl);
        int tempCurrentEl = currentEl;
        while (tempCurrentEl && array[parent] > key) {
            //cout<<tempCurrentEl<<" "<<  array[parent]<< " "<<key<<endl;
            std::swap(array[parent], array[tempCurrentEl]);
            tempCurrentEl = parent;
            parent = getParentPos(tempCurrentEl);
        }
        currentEl++;
    }

    void removeMin() {
        std::swap(array[0], array[currentEl-1]);
        currentEl--;
        int currentIndex = 0;
        while(currentIndex < currentEl) {
            int positionToBeSwapped = currentIndex;
            int leftChild = currentIndex * 2 + 1;
            int rightChild = currentIndex * 2 + 2;

            if (leftChild < currentEl && array[leftChild] < array[positionToBeSwapped]) {
                positionToBeSwapped = leftChild;
            }
            if (rightChild < currentEl && array[rightChild] < array[positionToBeSwapped]) {
                positionToBeSwapped = rightChild;
            }
            if (currentIndex == positionToBeSwapped) {
                break;
            } else {
                swap(array[positionToBeSwapped], array[currentIndex]);
                currentIndex = positionToBeSwapped;
            }
        }
    }

    int getMin() {
        return array[0];
    }
};

int main() {
    BinaryHeap bh;
    bh.add(1);
    bh.add(2);
    bh.add(-2);
    bh.add(-9);
    bh.add(12);
    bh.add(-2);
    bh.add(-23);
    bh.add(12);
    cout<<bh.getMin()<<endl;
    bh.removeMin();
    cout<<bh.getMin()<<endl;
    return 0;
}
