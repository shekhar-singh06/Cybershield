#include "httplib.h"
#include "ParkingLot.h"

#include <iostream>

#include "ParkingLot.cpp"
#include "waitingqueue.cpp"
#include "ActionLog.cpp"
#include "ParkingSlots.cpp"
#include "UndoStack.cpp"
#include "VehicleHashMap.cpp"

using namespace std;

void setCORS(httplib::Response& res) {
    res.set_header("Access-Control-Allow-Origin", "*");
    res.set_header("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
    res.set_header("Access-Control-Allow-Headers", "Content-Type");
}

int main()
{
    ParkingLot parkingLot;
    httplib::Server svr;

    // OPTIONS (CORS Preflight)
    svr.Options(R"(/api/.*)", [](const httplib::Request&, httplib::Response& res) {
        setCORS(res);
        res.status = 200;
    });

    // 1. STATUS
    svr.Get("/api/status", [&](const httplib::Request&, httplib::Response& res) {
        setCORS(res);
        res.set_content(parkingLot.getStatus(), "application/json");
    });

    // 2. ENTRY
    svr.Post("/api/entry", [&](const httplib::Request& req, httplib::Response& res) {
        setCORS(res);
        string plate = req.get_param_value("plate");
        string type = req.get_param_value("type");
        res.set_content(parkingLot.vehicleEntry(plate, type), "application/json");
    });

    // 3. EXIT
    svr.Post("/api/exit", [&](const httplib::Request& req, httplib::Response& res) {
        setCORS(res);
        string plate = req.get_param_value("plate");
        res.set_content(parkingLot.vehicleExit(plate), "application/json");
    });

    // 4. UNDO
    svr.Post("/api/undo", [&](const httplib::Request&, httplib::Response& res) {
        setCORS(res);
        res.set_content(parkingLot.undoLastAction(), "application/json");
    });

    // 5. SEARCH
    svr.Get("/api/search", [&](const httplib::Request& req, httplib::Response& res) {
        setCORS(res);
        string plate = req.get_param_value("plate");
        res.set_content(parkingLot.searchVehicle(plate), "application/json");
    });

    cout << "============================================\n";
    cout << "       PARKFLOW SERVER RUNNING              \n";
    cout << "       PORT: 8080                           \n";
    cout << "============================================\n";

    svr.listen("0.0.0.0", 8080);

    return 0;
}