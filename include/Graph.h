#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include<unordered_map>
#include<vector>
#include "station.h"
// take inputs and storing the data in graph
class Graph{
    
    public:

    // loads the data from csv files
    bool loadfromCSV(const std::string& data);

    //adds connection to the graph and here for primitive arguments we don' pass by refernce and for others we use pass by refernce
    // example for primitive int,float
    void AddConnection(const std::string& staA,const std::string& staB, int ,const std::string line);

    bool hasStation(const std::string& name) const;

    const std::vector<Edge>& getNeighbhours(const std::string& sta) const;
        //reurn all the station in the graph or network
    const std::vector<Edge> getAllStation() const;

        // return all the stations inline function
    size_t allStations() const {return adjacencyList.size();}
    size_t EdgeCount() const {return totalEdges;}

    private:

    std::unordered_map<std::string, std::vector<Edge>> adjacencyList;
    size_t totalEdges;

    // if a edge not there and for the lookupmisses for getneighbhous
    //which will succsfully returns a empty list
    static const std::vector<Edge> emptylist;

};

#endif