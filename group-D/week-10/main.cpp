#include <iostream>
#include <list>
using namespace std;

struct Pair {
    char first, second;
    Pair(char first, char second) {
        this->first = first;
        this->second = second;
    }
};

bool isDirectPath(const list<Pair>& graph, char from, char to) {
    for(Pair el : graph) {
        if ((el.first == from && el.second == to) ||
                (el.first == to && el.second == from)) {
            return true;
        }
    }
    return false;
};

void addEdge(list<Pair>& graph, char from, char to) {
    graph.push_front(Pair(from, to));
    return;
}

void showAllDirectPaths(list<Pair>& graph, char from) {
    for(Pair el : graph) {
        if (el.first == from) {
            cout<<el.second<<" ";
        }
        if (el.second == from) {
            cout<<el.first<<" ";
        }

    }
    return;
}

int main() {
    // Where we keep the vertex?
    list<Pair> graph;
    int n;
    cin>>n;
    char first,second;
    for (int i=0;i<n;i++) {
        cin>>first>>second;
        addEdge(graph, first,second);
    }
    cin>>first>>second;
    cout<<isDirectPath(graph, first, second)<<second;

    cin>>first;
    showAllDirectPaths(graph, first);

    return 0;
}
