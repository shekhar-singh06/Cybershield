#ifndef PARKINGLOT_H
#define PARKINGLOT_H

#include <string>
#include <vector>
#include <queue>

#include "ParkingSlots.h"
#include "waitingqueue.h"
#include "VehicleHashMap.h"
#include "UndoStack.h"

using namespace std;

class ParkingLot
{
private:
    ParkingSlots slots;
    waitingqueue waitingqueue;
    VehicleHashMap vehicleMap;
    UndoStack undoStack;

    string vectorToJson(const vector<string>& vec);
    string queueToJson(queue<string> q);

public:
    ParkingLot();

    string getStatus();

    string vehicleEntry(string plate, string type);

    string vehicleExit(string plate);

    string undoLastAction();

    string searchVehicle(string plate);

    size_t getStackSize();
};

#endif