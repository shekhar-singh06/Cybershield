#include "ActionLog.h"

ActionLog::ActionLog()
{
    plate = "";
    slotType = "";
    slotIndex = -1;
}

ActionLog::ActionLog(string p, string t, int i)
{
    plate = p;
    slotType = t;
    slotIndex = i;
}

string ActionLog::getPlate() const
{
    return plate;
}

string ActionLog::getSlotType() const
{
    return slotType;
}

int ActionLog::getSlotIndex() const
{
    return slotIndex;
}