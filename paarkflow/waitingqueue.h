#ifndef waitingqueue_H
#define waitingqueue_H

#include <queue>
#include <string>
using namespace std;

class waitingqueue
{
private:
    queue<string> q;

public:
    void push(string plate);
    void pop();

    string front();

    bool empty();

    queue<string> getQueue();
};

#endif
