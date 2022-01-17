#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    std::vector<int> numbers;
    int n;
    std::cin>>n;
    for(int i=0; i<n; i++)
    {
        int num;
        std::cin>>num;
        numbers.push_back(num);
    }

    int min_diff = INT_MAX;
    std::sort(numbers.begin(), numbers.end());
    for(int i=0; i<n-1; i++)
    {
        int diff = numbers[i+1] - numbers[i];
        min_diff = std::min(min_diff, diff);
    }

    std::cout<<min_diff<<std::endl;
    return 0;
}