#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include<unordered_map>
#include<vector>
#include "station.h"
class Graph{
    
    public:

    // loads the data from csv files
    bool loadfromCSV( std::string& data);

    //adds connection to the graph and here for primitive arguments we don' pass by refernce and for others we use pass by refernce
    // example for primitive int,float
    void AddConnection( std::string& staA, std::string& staB, int travelminutes);

    bool hasStation( std::string& name) ;

     std::vector<Edge> getNeighbours( std::string& sta) ;
        //reurn all the station in the graph or network
     std::vector<std::string> getAllStation() ;

        // return all the stations inline function
    size_t allStations()  {return adjacencyList.size();}
    size_t EdgeCount()  {return totalEdges;}

    private:

    std::unordered_map<std::string, std::vector<Edge>> adjacencyList;
    size_t totalEdges = 0;

    // if a edge not there and for the lookupmisses for getneighbhous
    //which will succsfully returns a empty list

};

#endif