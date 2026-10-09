#include "ParkingLot.h"

ParkingLot::ParkingLot()
{
}

string ParkingLot::vectorToJson(const vector<string>& vec)
{
    string json = "[";

    for (size_t i = 0; i < vec.size(); i++)
    {
        json += "\"" + vec[i] + "\"";

        if (i < vec.size() - 1)
            json += ",";
    }

    json += "]";

    return json;
}

string ParkingLot::queueToJson(queue<string> q)
{
    string json = "[";

    while (!q.empty())
    {
        json += "\"" + q.front() + "\"";

        q.pop();

        if (!q.empty())
            json += ",";
    }

    json += "]";

    return json;
}

string ParkingLot::getStatus()
{
    string json = "{";

    json += "\"regular\":";
    json += vectorToJson(slots.getRegularSlots());

    json += ",";

    json += "\"vip\":";
    json += vectorToJson(slots.getVIPSlots());

    json += ",";

    json += "\"queue\":";
    json += queueToJson(waitingqueue.getQueue());

    json += ",";

    json += "\"stackSize\":";
    json += to_string(undoStack.size());

    json += "}";

    return json;
}

string ParkingLot::vehicleEntry(string plate, string type)
{
    if (plate.empty())
    {
        return "{\"status\":\"error\",\"message\":\"License Plate is required!\"}";
    }

    string allocated = "";
    ActionLog action;

    // VIP Slot Allocation
    if (type == "VIP")
    {
        int index = slots.getFreeVIPSlot();

        if (index != -1)
        {
            slots.occupyVIP(index, plate);
            allocated = "VIP Slot " + to_string(index + 1);
            action = ActionLog(plate, "VIP", index);
        }
    }

    // Regular Slot Allocation
    if (allocated == "")
    {
        int index = slots.getFreeRegularSlot();

        if (index != -1)
        {
            slots.occupyRegular(index, plate);
            allocated = "Regular Slot " + to_string(index + 1);
            action = ActionLog(plate, "REGULAR", index);
        }
    }

    // Queue Allocation
    if (allocated == "")
    {
        waitingqueue.push(plate);
        allocated = "Waiting Queue (FIFO)";
        action = ActionLog(plate, "QUEUE", -1);
    }

    vehicleMap.insert(plate, allocated);
    undoStack.push(action);

    return "{\"status\":\"success\",\"location\":\"" + allocated + "\"}";
}

// 1. VEHICLE EXIT HANDLER
string ParkingLot::vehicleExit(string plate)
{
    if (plate.empty() || !vehicleMap.exists(plate))
    {
        return "{\"status\":\"error\",\"message\":\"Vehicle not found in Parking Lot!\"}";
    }

    string loc = vehicleMap.getLocation(plate);
    vehicleMap.remove(plate);

    // Free slot based on location string
    if (loc.find("VIP") != string::npos) {
        int idx = stoi(loc.substr(loc.find_last_of(' ') + 1)) - 1;
        slots.freeVIP(idx);
    } else if (loc.find("Regular") != string::npos) {
        int idx = stoi(loc.substr(loc.find_last_of(' ') + 1)) - 1;
        slots.freeRegular(idx);
    }

    // Allocate newly freed slot to queued car if queue is not empty
    if (!waitingqueue.empty()) {
        string nextPlate = waitingqueue.front();
        waitingqueue.pop();

        if (loc.find("VIP") != string::npos) {
            int idx = stoi(loc.substr(loc.find_last_of(' ') + 1)) - 1;
            slots.occupyVIP(idx, nextPlate);
            vehicleMap.insert(nextPlate, "VIP Slot " + to_string(idx + 1));
        } else if (loc.find("Regular") != string::npos) {
            int idx = stoi(loc.substr(loc.find_last_of(' ') + 1)) - 1;
            slots.occupyRegular(idx, nextPlate);
            vehicleMap.insert(nextPlate, "Regular Slot " + to_string(idx + 1));
        }
    }

    return "{\"status\":\"success\",\"message\":\"exited successfully!\"}";
}

// 2. CLEAN UNDO LAST ACTION HANDLER
string ParkingLot::undoLastAction()
{
    if (undoStack.empty())
    {
        return "{\"status\":\"error\",\"message\":\"No actions available to undo!\"}";
    }

    ActionLog lastAction = undoStack.top();
    undoStack.pop();

    string plate = lastAction.getPlate();
    string type = lastAction.getSlotType();
    int index = lastAction.getSlotIndex();

    if (type == "VIP") {
        slots.freeVIP(index);
        vehicleMap.remove(plate);
    } else if (type == "REGULAR") {
        slots.freeRegular(index);
        vehicleMap.remove(plate);
    } else if (type == "QUEUE") {
        queue<string> q = waitingqueue.getQueue();
        queue<string> updatedQ;

        while (!q.empty()) {
            if (q.front() != plate) {
                updatedQ.push(q.front());
            }
            q.pop();
        }
        
        while (!waitingqueue.empty()) {
            waitingqueue.pop();
        }
        
        while (!updatedQ.empty()) {
            waitingqueue.push(updatedQ.front());
            updatedQ.pop();
        }

        vehicleMap.remove(plate);
    }

    return "{\"status\":\"success\",\"message\":\"Undone last action for vehicle " + plate + "\"}";
}

// 3. SEARCH VEHICLE HANDLER (HASH MAP O(1))
string ParkingLot::searchVehicle(string plate)
{
    if (vehicleMap.exists(plate))
    {
        string location = vehicleMap.getLocation(plate);
        return "{\"found\":true,\"location\":\"" + location + "\"}";
    }

    return "{\"found\":false,\"location\":\"\"}";
}

size_t ParkingLot::getStackSize()
{
    return undoStack.size();
}