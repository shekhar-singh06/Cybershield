#include "VehicleHashMap.h"

void VehicleHashMap::insert(string plate, string location)
{
    vehicleMap[plate] = location;
}

bool VehicleHashMap::exists(string plate)
{
    return vehicleMap.find(plate) != vehicleMap.end();
}

string VehicleHashMap::getLocation(string plate)
{
    auto it = vehicleMap.find(plate);

    if (it != vehicleMap.end())
        return it->second;

    return "";
}

void VehicleHashMap::remove(string plate)
{
    vehicleMap.erase(plate);
}
