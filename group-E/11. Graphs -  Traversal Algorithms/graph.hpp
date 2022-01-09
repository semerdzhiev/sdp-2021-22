#pragma once
#include <vector>

//NB - unweighted graph
class graph
{
public:
    graph() = default;
    graph(unsigned int);
    void add_edge(unsigned int, unsigned int);
    bool is_connected() const;
    int min_distance_from_to(unsigned int, unsigned int) const;
private:
    void dfs(unsigned int, std::vector<bool>&) const;
    std::vector<std::vector<int>> adj_list{};
    unsigned int size{};
};