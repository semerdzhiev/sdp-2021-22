#include <iostream>
#include <vector>
#include <algorithm>

bool compare(int a, int b)
{
    return b < a;
}

int main()
{
    int n;
    std::cin>>n;
    std::vector<int> A, B;
    for(int i=0; i<n; i++)
    {
        int num;
        std::cin>>num;
        A.push_back(num);
    }
    for(int i=0; i<n; i++)
    {
        int num;
        std::cin>>num;
        B.push_back(num);
    }
    std::sort(A.begin(), A.end());
    std::sort(B.begin(), B.end(), &compare);
    int sumProduct = 0;
    for(int i=0; i<n; i++)
    {
        sumProduct += A[i]*B[i];
    }
    std::cout<<sumProduct<<std::endl;
    return 0;
}