#include<iostream>
using namespace std;

int linearSearch(int array[], int size, int seekedNumber) {
    for (int currentIndex = 0; currentIndex < size; currentIndex++)
    {
        if (array[currentIndex] == seekedNumber)
        {
            return currentIndex;
        }
    }
    return -1;
}

int binarySearch(int array[], int left, int right, int seekedNumber) {
    if (left <= right) {
        int mid = (left + right) / 2;
        if (array[mid] == seekedNumber)
            return mid;
        if (array[mid] > seekedNumber)
            return binarySearch(array, left, mid - 1, seekedNumber);
        if (array[mid] < seekedNumber)
            return binarySearch(array, mid + 1, right, seekedNumber);
    }
    return -1;
}

int main()
{
    int array[] = {1, 324, -32, 3, -8542, 1024, 8};
    //int array[] = { -8234, -123, 3, 5, 204, 1235, 2345 };
    int size = 7;

    int seekedNumber = 1024;

    cout << linearSearch(array, 0, size - 1, seekedNumber);

    return 0;
}