#include <vector>
#include <stdexcept>

class graph
{
public:
    graph() = default;
    graph(unsigned int n) : adj_list(n), n(n)
    {
    }
    void add_edge(int v1, int v2)
    {
        if (v1 >= n || v2 >= n)
        {
            throw std::out_of_range("Vertex index out of range");
        }
        // 1 2
        adj_list[v1].push_back(v2);
        adj_list[v2].push_back(v1);
    }
    bool is_connected() const
    {
        bool flag = false;
        std::vector<bool> visited(n, false);
        for (int i = 0; i < n; i++)
        {
            if (!visited[i])
            {
                if (flag)
                {
                    return false;
                }
                else
                {
                    dfs(i, visited);
                    flag = true;
                }
            }
        }
        return true;
    }

private:
    std::vector<std::vector<int>> adj_list{};
    void bfs()
    {
    }
    void dfs(int vertex, std::vector<bool> &visited) const
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
    unsigned int n{};
};