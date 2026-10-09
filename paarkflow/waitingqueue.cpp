#include "waitingqueue.h"

void waitingqueue::push(string plate)
{
    q.push(plate);
}

void waitingqueue::pop()
{
    if (!q.empty())
        q.pop();
}

string waitingqueue::front()
{
    if (q.empty())
        return "";

    return q.front();
}

bool waitingqueue::empty()
{
    return q.empty();
}

queue<string> waitingqueue::getQueue()
{
    return q;
}
