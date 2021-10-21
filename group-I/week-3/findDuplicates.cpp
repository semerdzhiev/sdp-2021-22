#include <iostream>
#include <algorithm>

using namespace std;

//Merge sort

void merge(int* arr1, int* arr2, size_t size1, size_t size2);

void mergeSort(int* arr, size_t size)
{
	if (size == 1)
	{
		return;
	}

	merge(arr, arr + size / 2, size / 2, size / 2 + size % 2);

}

void merge(int* arr1, int* arr2, size_t size1, size_t size2)
{
	mergeSort(arr1, size1);
	mergeSort(arr2, size2);

	int* newArr = new int[size1 + size2];

	int i = 0, j = 0;

	while (i + j < size1 + size2)
	{
		if (i < size1 && j < size2 && arr1[i] <= arr2[j])
		{
			newArr[i + j] = arr1[i];
			i++;
		}
		else if (j < size2)
		{
			newArr[i + j] = arr2[j];
			j++;
		}
		else if (j == size2)
		{
			newArr[i + j] = arr1[i];
			i++;
		}
		else if (i == size1)
		{
			newArr[i + j] = arr2[j];
			j++;
		}
	}

	for (int i = 0; i < size1; i++)
	{
		arr1[i] = newArr[i];
	}

	for (int i = 0; i < size2; i++)
	{
		arr2[i] = newArr[i + size1];
	}

	/*for (int i = 0; i < size1; i++)
	{
		std::cout << arr1[i] << std::endl;
	}

	for (int i = 0; i < size2; i++)
	{
		std::cout << arr2[i] << std::endl;
	}*/

	delete[] newArr;
}

//End of merge sort

// O(n^2)
int findDuplicate(int arr[], int size) {
	for (int candidateIndex = 0; candidateIndex < size; ++candidateIndex) {
		for (int candidate2Index = candidateIndex + 1; candidate2Index < size; ++candidate2Index) {
			if (arr[candidateIndex] == arr[candidate2Index]) {
				return arr[candidateIndex];
			}
		}
	}

	return -1;
}

// O(nlogn)
int findDuplicate2(int arr[], int size) {
	mergeSort(arr, size);
	for (int candidateIndex = 0; candidateIndex < size; ++candidateIndex) {
		if (candidateIndex < size - 1 && arr[candidateIndex] == arr[candidateIndex + 1]) {
			return arr[candidateIndex];
		}
	}

	return -1;
}

// O(n), O(int_size)
// find max element
// allocate dynamic bool array with such memory with elements set to 'false'
// iterate original array, set element to 'true' in the one we made
// if we find element to be already 'true', we return the element value
// delete dynamic array

int main() {
	int n;
	int arr[10000];

	cin >> n;
	for (int i = 0; i < n; ++i) {
		cin >> arr[i];
	}

	cout << findDuplicate2(arr, n) << endl;

	return 0;
}

