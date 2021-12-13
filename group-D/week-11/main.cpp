#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#define MAX_N 10
using namespace std;

bool g[MAX_N][MAX_N];
int gD[MAX_N][MAX_N];

bool isPath(int from, int to) { // BFS implementation
    bool used[MAX_N] = {0};
    used[from] = 1;
    queue<int> q;
    q.push(from);
    while (!q.empty()) {
        int c = q.front();
        q.pop();
        for (int i =0;i<MAX_N;i++) {
            if (g[c][i] && used[i] == false) {
                if (i == to) {
                    return true;
                }
                q.push(i);
                used[i] = 1;
            }
        }
    }
    return false;
}

void displayAllPaths(int from, bool *used, vector<int>& s) { //DFS
    bool lastEl = true;
    for (int i =0; i<MAX_N; i++) {
        if (g[from][i] && used[i] == false) {
            lastEl = false;
            s.push_back(i);
            used[i] = 1;
            //?
            displayAllPaths(i, used, s);
            s.pop_back();
            used[i] = 0;
        }
    }
    if (lastEl) {
        for(int el:s) {
            cout<<"-->"<<el;
        }
        cout<<endl;
    }
    return;

}

struct Edge {
    int from;
    int to;
    int w;
    Edge( int from, int to, int w) {
        this->from = from;
        this->to = to;
        this->w = w;
    }
    friend bool operator<(const Edge&, const Edge&);
};

bool operator<(const Edge& first, const Edge& second) {
    return first.w < second.w;
}

void priorityDijkstra(int from) {
    int shortestPath[MAX_N];
    for (int i=0;i<MAX_N;i++) {shortestPath[i] = 99999;}
    shortestPath[from] = 0;
    priority_queue<Edge> q;
    for (int i=0;i<MAX_N;i++) {
        if (gD[from][i]) {
            q.push(Edge(from, i, gD[from][i]));
        }
    }
    while(!q.empty()) {
        Edge c = q.top();
        q.pop();
        if (shortestPath[c.to] > shortestPath[c.from] + c.w) {
            shortestPath[c.to] = shortestPath[c.from] + c.w;
            for (int i=0;i<MAX_N;i++) {
                if (gD[c.to][i]) {
                    q.push(Edge(c.to, i, gD[c.to][i]));
                }
            }
        }
    }
    for (int i=0;i<MAX_N;i++) {
        cout<<i << " "<< shortestPath[i]<<endl;
    }
    return;

}
int main() {
    g[1][3] = 1;
    g[3][4] = 1;
    g[4][5] = 1;
    g[4][6] = 1;
    g[5][6] = 1;
    g[5][7] = 1;
    g[5][8] = 1;
    g[2][5] = 1;
    g[1][4] = 1;

    bool used[MAX_N] = {0};
    vector<int> s;
    s.push_back(1);
    used[1] = 1;
    cout<<isPath(1, 8)<<endl;
    cout<<isPath(5, 2)<<endl;
    displayAllPaths(1, used, s);
//    gD[2][7] = 100;
//    gD[2][3] = 3;
//    gD[3][7] = 100;
//    gD[2][4] = 3;
//    gD[4][7]= 5;
    gD[2][3] = 2;
    gD[3][4] = 3;
    gD[4][6] = 2;
    gD[6][9] = 1;
    gD[4][9] = 4;
    gD[2][6] = 150;
    gD[6][9] = 1;
    gD[2][1] = 1;
    gD[1][9] = 150;
    priorityDijkstra(2);
    return 0;
}
