#include <iostream>
#include <vector>

//0 - ...000 - {}
//1 - ...001 - {5}
//2 - ...010 - {7}
//3 - ...011 - {8, 5}
//...
//7 - ...111 - {1, 8, 5} 

//example :
//subset = 6 -> ..110
//i = 0 -> mask = ...001 => 0 => 5 N
//i = 1 -> mask = ...010 => 1 => 8 Y
//i = 2 -> mask = ...100 => 1 => 1 Y => {8, 1}
void print_subset(size_t subset, const std::vector<int> set)
{
    int mask = 1;

    std::cout << "{ ";

    for(size_t i = 0; i < set.size(); ++i)
    {
        if(subset & mask)
            std::cout << set[set.size() - 1 - i] << " ";

        mask <<= 1;
    }

    std::cout << '}' << std::endl;
}

void get_subsets_it(const std::vector<int>& set)
{
    size_t subsets_count = 1 << set.size();

    for(size_t i = 0; i < subsets_count; ++i)
    {
        print_subset(i, set);
    }
}

void print(const std::vector<int>& subset)
{
    std::cout << "{ ";

    for(size_t i = 0; i < subset.size(); ++i)
            std::cout << subset[i] << " ";

    std::cout << '}' << std::endl;    
}

void get_subsets_rec(const std::vector<int>& set, std::vector<int>& subset, size_t used = 0)
{
    if(used == set.size())
    {
        print(subset);
        return;
    }

    get_subsets_rec(set, subset, used + 1);

    subset.push_back(set[used]);
    get_subsets_rec(set, subset, used + 1);
    subset.pop_back();
}

void get_subsets_rec_wrapper(const std::vector<int>& set)
{
    std::vector<int> subset;
    get_subsets_rec(set, subset);
}

void get_permutations(const std::vector<int>& set, std::vector<int>& permutation, std::vector<bool>& used)
{
    if(permutation.size() == set.size())
    {
        print(permutation);
        return;
    }

    for(size_t i = 0; i < set.size(); ++i)
    {
        if(!used[i])
        {
            permutation.push_back(set[i]);
            used[i] = 1;
            get_permutations(set, permutation, used);
            permutation.pop_back();
            used[i] = 0;
        }
    }
}

void get_permutations_wrapper(const std::vector<int>& set)
{
    std::vector<int> permutation;
    std::vector<bool> used;
    used.resize(set.size(), 0);
    get_permutations(set, permutation, used);
}

void get_variations(const std::vector<int>& set, std::vector<int>& variation, std::vector<bool>& used, size_t k)
{
    if(variation.size() == k)
    {
        print(variation);
        return;
    }

    for(size_t i = 0; i < set.size(); ++i)
    {
        if(!used[i])
        {
            variation.push_back(set[i]);
            used[i] = 1;
            get_variations(set, variation, used, k);
            variation.pop_back();
            used[i] = 0;
        }
    }
}

void get_variations_wrapper(const std::vector<int>& set, size_t k)
{
    std::vector<int> variation;
    std::vector<bool> used;
    used.resize(set.size(), 0);
    get_variations(set, variation, used, k);
}

void get_combinations(const std::vector<int>& set, std::vector<int>& combination, std::vector<bool> used, size_t k)
{
    if(combination.size() == k)
    {
        print(combination);
        return;
    }

    for(size_t i = 0; i < set.size(); ++i)
    {
        if(!used[i])
        {
            combination.push_back(set[i]);
            used[i] = 1;
            get_combinations(set, combination, used, k);
            combination.pop_back();
        }
    }
}

void get_combinations_wrapper(const std::vector<int>& set, size_t k)
{
    std::vector<int> combination;
    std::vector<bool> used;
    used.resize(set.size(), 0);
    get_combinations(set, combination, used, k);
}

int main()
{

    std::vector<int> set;

    set.push_back(1);
    set.push_back(8);
    set.push_back(3);
    set.push_back(5);
    set.push_back(10);

    get_combinations_wrapper(set, 2);

    return 0;
}