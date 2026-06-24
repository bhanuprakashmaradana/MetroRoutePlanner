#ifndef BFS_H
#define BFS_H

#include <string>
#include <vector>
#include "Graph.h"


struct RouteResult {
    bool found = false;
    std::vector<std::string> path;
    int stopCount = 0;
    int totalTravelTimeMinutes = 0;
};

RouteResult findRouteBFS( Graph& graph, std::string& source, std::string& destination);

#endif // BFS_H
