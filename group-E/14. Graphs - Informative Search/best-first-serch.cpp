#include <iostream>
#include <vector>
#include <queue>
#include <string>

struct NodeValue
{
    int node;
    int value;
    bool operator>(const NodeValue &other) const
    {
        return value > other.value;
    }
};

int main()
{
    int n, m, s, d;
    std::cin >> n >> m;
    std::cin >> s >> d;
    std::vector<std::vector<int>> adj_list(n);
    std::vector<int> h(n);
    for (int i = 0; i < m; i++)
    {
        int x, y;
        std::cin >> x >> y;
        adj_list[x].push_back(y);
        adj_list[y].push_back(x);
    }

    //heuristic
    for (int i = 0; i < n; i++)
    {
        std::cin >> h[i];
    }

    std::priority_queue<NodeValue, std::vector<NodeValue>, std::greater<NodeValue>> pq;
    std::vector<bool> used(n, false);
    std::vector<int> parent(n);
    pq.push({s, h[s]});
    used[s] = true;
    parent[s] = -1;
    while (!pq.empty())
    {
        auto current = pq.top();
        pq.pop();
        for (auto adj : adj_list[current.node])
        {
            if (adj == d)
            {
                //find path
                std::string path = "";
                int node = d;
                while (node != s)
                {
                    path = std::to_string(node) + " " + path;
                    node = parent[node];
                }
                path = std::to_string(s) + " " + path;
                std::cout << path << std::endl;
                return 0;
            }
            if (!used[adj])
            {
                used[adj] = true;
                parent[adj] = current.node;
                pq.push({adj, h[adj]});
            }
        }
    }
    std::cout << "No path from start to begin" << std::endl;
    return 0;
}