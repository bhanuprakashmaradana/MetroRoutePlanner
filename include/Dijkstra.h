#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <string>
#include "Graph.h"
#include "BFS.h" 


RouteResult findRouteDijkstra( Graph& graph, std::string& source, std::string& destination);

#endif 
