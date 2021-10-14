#include <iostream>

using namespace std;

template <typename T>
void swap(T* a, T* b) {
    T temp = *a;
    *a = *b;
    *b = temp;
}

int main()
{
    int a = 5;
    int b = 6;

    swap(&a, &b);

    cout << a << " " << b;

    return 0;
}