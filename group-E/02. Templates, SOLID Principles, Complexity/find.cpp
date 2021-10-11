#include <iostream>

template <typename T>
T *find(T *begin, T* end, T elem)
{
    while(begin <= end)
    {
        if (*begin == elem)
        {
            return begin;
        }
        ++begin;
    }
    return nullptr;
}

int main()
{
    int arr[5] = {1, 2, 3, 7, 8};
    int* pointer = find(arr, arr + 4, 10);
    if (pointer == nullptr)
    {
        std::cout << "NOT FOUND\n";
    }
    else
        std::cout << *pointer << std::endl;
    return 0;
}