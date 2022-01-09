#include "graph.hpp"
#include <iostream>

int main()
{
    graph g{7};
    g.add_edge(0, 1);
    g.add_edge(1, 2);
    g.add_edge(2, 3);
    g.add_edge(3, 4);
    g.add_edge(4, 5);
    g.add_edge(4, 6);
    g.add_edge(6, 2);
    g.add_edge(6, 5);
    std::cout << g.min_distance_from_to(6, 4) << " " << g.min_distance_from_to(4, 6) << std::endl;
    std::cout << g.is_connected() << std::endl;
    return 0;
}