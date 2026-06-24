#include "Graph.h"
#include <fstream>
#include<iostream>
#include<sstream>
 using namespace std;
 

 void Graph::AddConnection( string& A, string& B,int travelMinutes ){
    adjacencyList[A].push_back({B,travelMinutes});
    adjacencyList[B].push_back({A,travelMinutes});
    totalEdges++;
 }
 bool Graph::loadfromCSV(string& filepath){
    ifstream file(filepath);
    if (!file.is_open()) {
        cerr << "Error: could not open data file: " << filepath << "\n";
        return false;
    }

    string line;
    bool isHeader = true;
    int lineNumber = 0;

    while (getline(file, line)) {
        lineNumber++;
        if (isHeader) { isHeader = false; continue; } 
        if (line.empty()) continue;

        stringstream ss(line);
        string stationA, stationB, weightStr;

        if (!getline(ss, stationA, ',') ||
            !getline(ss, stationB, ',') ||
            !getline(ss, weightStr, ',') 
            ) {
            cerr << "Warning: malformed row at line " << lineNumber
                      << ", skipping.\n";
            continue;
        }
         auto trimStr = [](string s) {
            size_t start = s.find_first_not_of(" \t\r\n");
            size_t end   = s.find_last_not_of(" \t\r\n");
            if (start == string::npos) return string("");
            return s.substr(start, end - start + 1);
        };
        stationA  = trimStr(stationA);
        stationB  = trimStr(stationB);
        weightStr = trimStr(weightStr);

        try {
            int weight = stoi(weightStr);
            AddConnection(stationA, stationB, weight);
        } catch (exception&) {
            cerr << "Warning: invalid travel time at line " << lineNumber
                      << ", skipping.\n";
        }
    }

    file.close();
    return true;
 }

  bool Graph::hasStation(string& name){
   auto it=adjacencyList.find(name);
   if(it==adjacencyList.end()) return false;
   return true;
 }


 vector<Edge> Graph::getNeighbours(string& sta){
   if(hasStation(sta)) return adjacencyList[sta];
   return {};
 }


 vector<string> Graph::getAllStation(){
   vector<string> stations;
   stations.reserve(adjacencyList.size());
   for(auto& pair : adjacencyList){
      stations.push_back(pair.first);
   }
   return stations;
 }