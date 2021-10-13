#include <iostream>
#include <algorithm>
using namespace std;

void printArr(int* arr, int size) {
    for(int i = 0; i< size; ++i) {
        cout<< arr[i]<< " ";
    }
    cout<< endl;
}

void printPermutations(int* arr, int startIndex, int size) {
    if(startIndex == size-1) {
        printArr(arr, size);
        return;
    }

    for(int i = startIndex; i< size; ++i) {
        swap(arr[startIndex], arr[i]);
        printPermutations(arr, startIndex+1, size);
        swap(arr[startIndex], arr[i]);
    }
}

int main() {
    int arr[] = {4, 1, 3, 2};
    int size = 4;

    printPermutations(arr, 0, size);

    return 0;
}
