#include "Graph.h"
#include <fstream>
#include<iostream>
#include<sstream>
 using namespace std;
 
  vector<Edge> Graph::emptylist;

 void Graph::AddConnection( string& A, string& B,int travelMinutes, string& line ){
    adjacencyList[A].push_back({B,travelMinutes,line});
    adjacencyList[B].push_back({A,travelMinutes,line});
    totalEdges++;
 }
 bool Graph::loadfromCSV(std::string& filepath){
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "Error: could not open data file: " << filepath << "\n";
        return false;
    }

    std::string line;
    bool isHeader = true;
    int lineNumber = 0;

    while (std::getline(file, line)) {
        lineNumber++;
        if (isHeader) { isHeader = false; continue; } // skip CSV header row
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string stationA, stationB, weightStr, lineName;

        if (!std::getline(ss, stationA, ',') ||
            !std::getline(ss, stationB, ',') ||
            !std::getline(ss, weightStr, ',') ||
            !std::getline(ss, lineName, ',')) {
            std::cerr << "Warning: malformed row at line " << lineNumber
                      << ", skipping.\n";
            continue;
        }

        try {
            int weight = std::stoi(weightStr);
            AddConnection(stationA, stationB, weight, lineName);
        } catch (const std::exception&) {
            std::cerr << "Warning: invalid travel time at line " << lineNumber
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


 vector<Edge>& Graph::getNeighbours(string& sta){
   if(hasStation(sta)) return adjacencyList[sta];
   return emptylist;
 }


 vector<string> Graph::getAllStation(){
   vector<string> stations;
   stations.reserve(adjacencyList.size());
   for(auto& pair : adjacencyList){
      stations.push_back(pair.first);
   }
   return stations;
 }