#include <iostream>

using namespace std;

int biggestDifference(int arr[], int n) {
    int currMinIndex = 0;
    int currMaxDifference = 0;
    for(int i = 1; i< n; ++i) {
        int currDifference = arr[i] - arr[currMinIndex];
        if(currDifference > currMaxDifference) {
            currMaxDifference = currDifference;
        }
        if(arr[i] < arr[currMinIndex]) {
            currMinIndex = i;
        }
    }
    return currMaxDifference;
}

int main()
{
    int stockPrices[] = {50, 400, 10, 7, 5, 1, 25, 525, 8, 11, 9};
    cout<< biggestDifference(stockPrices, 11);

    return 0;
}
