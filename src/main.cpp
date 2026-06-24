
#include <iostream> //cin cout 
#include <chrono> // measuring time
#include <algorithm> // sort and transform
#include <cctype> // tolower
#include "Graph.h"
#include "BFS.h"
#include "Dijkstra.h"

using namespace std;
using namespace std::chrono;
string takeExtra(string s) {
    size_t start = s.find_first_not_of(" \t\r\n"); // to trim the starting charecter that is letter 
    size_t end = s.find_last_not_of(" \t\r\n");// ending charecter that is letter
    if (start == string::npos) return ""; //if no charecter is present other than /t /n /t
    return s.substr(start, end - start + 1);
}

string convertLower(string s) {
    string out = s;
   transform(out.begin(), out.end(), out.begin(),[](unsigned char c){ return tolower(c); });
    return out;
}


string resolveStationName( Graph& graph, string& input) {
    string target = convertLower(takeExtra(input));
    for ( auto& station : graph.getAllStation()) {
        if (convertLower(station) == target) return station;
    }
    return "";
}

static void printPath(const RouteResult& r) {
    for (size_t i = 0; i < r.path.size(); i++) {
        cout << r.path[i];
        if (i + 1 < r.path.size()) cout << "  ->  ";
    }
    cout << "\n";
}

static void runQuery( Graph& graph, string& source,string& destination, bool useDijkstra) {
    auto start = high_resolution_clock::now();

    RouteResult result = useDijkstra
        ? findRouteDijkstra(graph, source, destination)
        : findRouteBFS(graph, source, destination);

    auto end = high_resolution_clock::now();
    double elapsedMs = duration<double, milli>(end - start).count();

    if (!result.found) {
        cout << "\nNo route found between \"" << source << "\" and \""<< destination << "\".\n\n";
        return;
    }

    cout << "\nAlgorithm:     " << (useDijkstra ? "Dijkstra (fastest by time)" : "BFS (fewest stops)") << "\n";
    cout << "Route:         ";
    printPath(result);
    cout << "Stops:         " << result.stopCount << "\n";
    cout << "Travel time:   " << result.totalTravelTimeMinutes << " minutes\n";
    cout << "Computed in:   " << elapsedMs << " ms\n\n";
}

static void printMenu() {
    cout << "\n========== Metro Route Planner ==========\n";
    cout << "1. Find route - fewest stops (BFS)\n";
    cout << "2. Find route - fastest time (Dijkstra)\n";
    cout << "3. List all stations\n";
    cout << "4. Show network stats\n";
    cout << "5. Exit\n";
    cout << "===========================================\n";
    cout << "Choice: ";
}

int main(int argc, char* argv[]) {
    Graph graph;
    string dataPath = (argc > 1) ? argv[1] : "data/metro_network.csv";

    cout << "Loading metro network from " << dataPath << " ...\n";
    if (!graph.loadfromCSV(dataPath)) {
        cerr << "Failed to load network. Exiting.\n";
        return 1;
    }
    cout << "Loaded " << graph.allStations() << " stations, "
              << graph.EdgeCount() << " connections.\n";

    while (true) {
        printMenu();
        string choice;
        getline(cin, choice);
        choice = takeExtra(choice);

        if (choice == "5") {
            cout << "Goodbye!\n";
            break;
        } else if (choice == "1" || choice == "2") {
            bool useDijkstra = (choice == "2");

            cout << "Source station: ";
            string srcInput;
            getline(cin, srcInput);
            string source = resolveStationName(graph, srcInput);
            if (source.empty()) {
                cout << "Unknown station: \"" << srcInput << "\"\n";
                continue;
            }

            cout << "Destination station: ";
            string dstInput;
            getline(cin, dstInput);
            string destination = resolveStationName(graph, dstInput);
            if (destination.empty()) {
                cout << "Unknown station: \"" << dstInput << "\"\n";
                continue;
            }

            runQuery(graph, source, destination, useDijkstra);

        } else if (choice == "3") {
            auto stations = graph.getAllStation();
            sort(stations.begin(), stations.end());
            cout << "\n" << stations.size() << " stations:\n";
            for ( auto& s : stations) cout << "  - " << s << "\n";
            cout << "\n";

        } else if (choice == "4") {
            cout << "\nStations: " << graph.allStations()<< "\nConnections: " << graph.EdgeCount() << "\n\n";

        } else {
            cout << "Invalid choice, try again.\n";
        }
    }

    return 0;
}
