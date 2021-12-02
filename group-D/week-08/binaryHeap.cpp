#include <iostream>
using namespace  std;
class BinaryHeap { // min heap
    int arr[100];
    int currentSize;
public:
    BinaryHeap() : currentSize(0) {};
    void insert(int el) {
        arr[currentSize] = el;
        int tempIndex = currentSize;
        while (tempIndex != 0) {
            if (arr[tempIndex] < arr[tempIndex / 2]) {
                swap(arr[tempIndex], arr[tempIndex / 2] );
                tempIndex = tempIndex / 2;
            } else break;

        }
        currentSize++;
    };
    void removeTop() {
        swap(arr[0], arr[currentSize -1]);
        currentSize--;
        int tempIndex = 0;
        while (tempIndex < currentSize / 2) {
            int leftChild = arr[2*tempIndex + 1];
            int rightChild = arr[2*tempIndex + 2];
            if (leftChild > arr[tempIndex] && arr[tempIndex] < rightChild ) {
                break; // Is this required validation;
            }
            if (leftChild > rightChild) {
                swap(arr[tempIndex],arr[2*tempIndex + 2]);
                tempIndex = 2*tempIndex + 2;
            } else {
                swap(arr[tempIndex],arr[2*tempIndex + 1]);
                tempIndex = 2*tempIndex + 1;
            }
            //swap(arr[tempIndex], min(arr[2*tempIndex + 1], arr[2*tempIndex + 2]))

        }

    }

    int getTop() {return arr[0];}

};

int main() {
    BinaryHeap bh;
    bh.insert(6);
    bh.insert(33);
    bh.insert(35);
    bh.insert(9);
    bh.insert(4);
    bh.insert(5);
    bh.insert(-25);
    bh.insert(125);
    cout<<bh.getTop()<<endl;
    bh.removeTop();
    cout<<bh.getTop()<<endl;
    bh.removeTop();
    cout<<bh.getTop();
    return 0;
}
