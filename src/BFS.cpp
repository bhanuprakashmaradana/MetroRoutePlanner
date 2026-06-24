#include "BFS.h"
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
using namespace std;
RouteResult findRouteBFS( Graph& graph, string& source, string& destination) {
    RouteResult result;

    if (!graph.hasStation(source) || !graph.hasStation(destination)) {
        return result; // found stays false
    }
    if (source == destination) {
        result.found = true;
        result.path = {source};
        return result;
    }

   
    queue<string> frontier;
    unordered_set<string> visited;
    unordered_map<string, string> parent;

    frontier.push(source);
    visited.insert(source);

    bool reached = false;
    while (!frontier.empty() && !reached) {
        string current = frontier.front();
        frontier.pop();

        for (const Edge& e : graph.getNeighbours(current)) {
            if (visited.count(e.Destination)) continue;
            visited.insert(e.Destination);
            parent[e.Destination] = current;

            if (e.Destination == destination) {
                reached = true;
                break;
            }
            frontier.push(e.Destination);
        }
    }

    if (!reached) return result; 

    vector<string> path;
    string node = destination;
    while (node != source) {
        path.push_back(node);
        node = parent[node];
    }
    path.push_back(source);
    reverse(path.begin(), path.end());

   
    int totalTime = 0;
    for (size_t i = 0; i + 1 < path.size(); ++i) {
        for (const Edge& e : graph.getNeighbours(path[i])) {
            if (e.Destination == path[i + 1]) {
                totalTime += e.weight;
                break;
            }
        }
    }

    result.found = true;
    result.path = path;
    result.stopCount = static_cast<int>(path.size()) - 1;
    result.totalTravelTimeMinutes = totalTime;
    return result;
}
