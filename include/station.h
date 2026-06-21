#ifndef STATION_H
#define STATION_H
#include<string>
// to store effective optimal information
struct Edge{
    std::string Destination;
    int Time;
    std::string line;

};
// to take the raw data from the input csv files
struct StationConnection {

    std::string Station_A;
    std::string Station_B;
    int Time;
    std::string Line; 
};


#endif