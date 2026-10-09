#include "ActionLog.h"
#ifndef UNDOSTACK_H
#define UNDOSTACK_H

#include <stack>
#include "ActionLog.h"

using namespace std;

class UndoStack
{
private:
    stack<ActionLog> s;

public:
    void push(ActionLog action);
    void pop();

    ActionLog top();

    bool empty();

    size_t size();
};

#endif
