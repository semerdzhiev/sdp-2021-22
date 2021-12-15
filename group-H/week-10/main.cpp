#include <iostream>
#include <queue>
#define MAX_N 10
using namespace std;

class Graph {
private:
    bool graph[MAX_N][MAX_N] = {{0}};
public:
    bool addPath(int from, int to) {
        graph[from][to] = true;
    }

    bool isDirectPath(int from, int to) {
        return graph[from][to];
    }

    bool isPath(int from, int to) {
        bool used[MAX_N] = {0};
        queue<int> q;
        q.push(from);
        used[from] = 1;
        while (!q.empty()) {
            if (used[to]) {
                return true;
            }
            int currentEl = q.front();
            q.pop();
            for (int i = 0;i<MAX_N; i++) {
                if (!used[i] && graph[currentEl][i]) {
                    q.push(i);
                    used[i] = 1;
                }
            }
        }
        return false;

    }

    void allDirectsPaths(int from) {
        for (int i =0;i<MAX_N;i++)
            if (graph[from][i]) cout<<i<<" ";

    }
};

int main() {
    Graph g;
    g.addPath(0,1);
    g.addPath(0,2);
    g.addPath(2,6);
    g.addPath(0,5);
    cout<<g.isDirectPath(0,3)<<endl;
    g.allDirectsPaths(0);
    cout<<endl<<g.isPath(0,6)<<endl;

   return 0;
}
