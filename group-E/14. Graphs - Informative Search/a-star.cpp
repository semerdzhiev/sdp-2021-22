#include <iostream>
#include <vector>
#include <queue>
#include <string>

struct NeighbourInfo
{
    int y;
    int distance;
};

struct NodeValue
{
    int node;
    int distance;
    bool operator>(const NodeValue &other) const
    {
        return distance > other.distance;
    }
};

int main()
{
    int n, m, s, d;
    std::cin >> n >> m;
    std::cin >> s >> d;
    std::vector<std::vector<NeighbourInfo>> adj_list(n);
    std::vector<int> h(n);
    for (int i = 0; i < m; i++)
    {
        int x, y, d;
        std::cin >> x >> y >> d;
        adj_list[x].push_back({y, d});
        adj_list[y].push_back({x, d});
    }

    //heuristic
    for (int i = 0; i < n; i++)
    {
        std::cin >> h[i];
    }

    std::priority_queue<NodeValue, std::vector<NodeValue>, std::greater<NodeValue>> pq;
    std::vector<int> parent(n);
    std::vector<int> dist(n, INT_MAX);
    pq.push({s, h[s]});
    dist[s] = 0;

    while (!pq.empty())
    {
        auto current = pq.top();
        pq.pop();

        if (current.node == d)
        {
            std::string path = "";
            int node = d;
            while (node != s)
            {
                path = std::to_string(node) + " " + path;
                node = parent[node];
            }
            path = std::to_string(s) + " " + path;
            std::cout << path << std::endl;
            std::cout << dist[d] << std::endl;
            return 0;
        }

        for (auto adj : adj_list[current.node])
        {
            if (dist[adj.y] > dist[current.node] + adj.distance)
            {
                dist[adj.y] = dist[current.node] + adj.distance;
                pq.push({adj.y, dist[adj.y] + h[adj.y]});
                parent[adj.y] = current.node;
            }
        }
    }

    std::cout << "No path from start to begin" << std::endl;

    return 0;
}