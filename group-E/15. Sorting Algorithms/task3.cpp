#include <vector>
#include <algorithm>
#include <iostream>

bool are_equal(const std::vector<int>& arr1, const std::vector<int>& arr2)
{
    int n1 = arr1.size();
    int n2 = arr2.size();
    if(n1 != n2)
    {
        return false;
    }
    std::sort(arr1.begin(), arr1.end());
    std::sort(arr2.begin(), arr2.end());
    for(int i=0; i<n1; i++)
    {
        if(arr1[i] != arr2[i])
        {
            return false;
        }
    }
    return true;
}

int main()
{
    // std::vector<int> arr1 = {1, 2, 7, -1, 1};
    // std::vector<int> arr2 = {7, 2, -1, 1, 1};
    // std::cout<<are_equal({1, 2, 7, -1, 1}, {7, 2, -1, 1, 1})<<std::endl;
}