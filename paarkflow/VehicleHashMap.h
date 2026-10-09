#ifndef VEHICLEHASHMAP_H
#define VEHICLEHASHMAP_H

#include <unordered_map>
#include <string>
using namespace std;

class VehicleHashMap
{
private:
    unordered_map<string, string> vehicleMap;

public:
    void insert(string plate, string location);

    bool exists(string plate);

    string getLocation(string plate);

    void remove(string plate);
};

#endif
