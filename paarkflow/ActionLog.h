#ifndef ACTIONLOG_H
#define ACTIONLOG_H

#include <string>

using namespace std;

class ActionLog
{
private:
    string plate;
    string slotType;
    int slotIndex;

public:
    ActionLog();
    ActionLog(string p, string t, int i);

    string getPlate() const;
    string getSlotType() const;
    int getSlotIndex() const;
};

#endif