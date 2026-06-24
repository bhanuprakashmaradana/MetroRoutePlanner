#include "Dijkstra.h"
#include <queue>
#include <unordered_map>
#include <limits>
#include <algorithm>
using namespace std;
RouteResult findRouteDijkstra( Graph& graph, string& source, string& destination) {
    RouteResult result;

    if (!graph.hasStation(source) || !graph.hasStation(destination)) {
        return result;
    }
    if (source == destination) {
        result.found = true;
        result.path = {source};
        return result;
    }

    unordered_map<string, int> dist;
    unordered_map<string, string> parent;

    
    using PQItem = pair<int, string>;
    priority_queue<PQItem, vector<PQItem>, greater<PQItem>> pq;

    for ( auto& station : graph.getAllStation()) {
        dist[station] = numeric_limits<int>::max();
    }
    dist[source] = 0;
    pq.push({0, source});

    while (!pq.empty()) {
        int currentDist=pq.top().first;
        string current = pq.top().second;
        pq.pop();

       
        if (currentDist > dist[current]) continue;
        if (current == destination) break; // early exit once settled

        for ( Edge& e : graph.getNeighbours(current)) {
            int newDist = currentDist + e.weight;
            if (newDist < dist[e.Destination]) {
                dist[e.Destination] = newDist;
                parent[e.Destination] = current;
                pq.push({newDist, e.Destination});
            }
        }
    }

    if (dist[destination] == numeric_limits<int>::max()) {
        return result; 
    }

    vector<string> path;
    string node = destination;
    while (node != source) {
        path.push_back(node);
        if (parent.find(node) == parent.end()) {
            // No parent found — path reconstruction broken, no route exists
            return result;
        }
        node = parent[node];
    }
    path.push_back(source);
    reverse(path.begin(), path.end());

    result.found = true;
    result.path = path;
    result.stopCount = static_cast<int>(path.size()) - 1;
    result.totalTravelTimeMinutes = dist[destination];
    return result;
}
 