#include "ParkingSlots.h"

ParkingSlots::ParkingSlots()
{
    regularSlots.resize(10, "FREE");
    vipSlots.resize(5, "FREE");
}

int ParkingSlots::getFreeRegularSlot()
{
    for (int i = 0; i < regularSlots.size(); i++)
    {
        if (regularSlots[i] == "FREE")
            return i;
    }

    return -1;
}

int ParkingSlots::getFreeVIPSlot()
{
    for (int i = 0; i < vipSlots.size(); i++)
    {
        if (vipSlots[i] == "FREE")
            return i;
    }

    return -1;
}

void ParkingSlots::occupyRegular(int index, string plate)
{
    regularSlots[index] = plate;
}

void ParkingSlots::occupyVIP(int index, string plate)
{
    vipSlots[index] = plate;
}

void ParkingSlots::freeRegular(int index)
{
    regularSlots[index] = "FREE";
}

void ParkingSlots::freeVIP(int index)
{
    vipSlots[index] = "FREE";
}

vector<string> ParkingSlots::getRegularSlots()
{
    return regularSlots;
}

vector<string> ParkingSlots::getVIPSlots()
{
    return vipSlots;
}
