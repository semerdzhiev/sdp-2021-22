#include "graph.hpp"
#include <queue>
#include <stdexcept>
#include <vector>

graph::graph(unsigned int n) : adj_list{n}, size{n} {}

void graph::add_edge(unsigned int from, unsigned int to)
{
    if (from > adj_list.size() || to > adj_list.size())
    {
        throw std::out_of_range("Too large vertex index");
    }
    adj_list[from].push_back(to);
    // undirected graph
    // adj_list[to][from] = 1;
}

bool graph::is_connected() const
{
    std::vector<bool> visited(size);
    bool flag = false;
    for (unsigned int i = 0; i < size; i++)
    {
        if (!visited[i])
        {
            if (flag)
            {
                return false;
            }
            dfs(i, visited);
            flag = true;
        }
    }
    return true;
}

int graph::min_distance_from_to(unsigned int from, unsigned int to) const
{
    std::vector<int> dist(size);
    std::vector<bool> visited(size);
    std::queue<int> bfs_queue{};
    bfs_queue.push(from);
    dist[from] = 0;
    visited[from] = 1;
    while (!bfs_queue.empty())
    {
        int current = bfs_queue.front();
        bfs_queue.pop();
        for (int adj : adj_list[current])
        {
            if (!visited[adj])
            {
                bfs_queue.push(adj);
                dist[adj] = dist[current] + 1;
                visited[adj] = true;
            }
        }
    }
    if (!visited[to])
        return -1;
    return dist[to];
}

void graph::dfs(unsigned int vertex, std::vector<bool> &visited) const
{
    for (int adj : adj_list[vertex])
    {
        if (!visited[adj])
        {
            visited[adj] = true;
            dfs(adj, visited);
        }
    }
}