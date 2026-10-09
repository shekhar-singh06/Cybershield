#include "UndoStack.h"

void UndoStack::push(ActionLog action)
{
    s.push(action);
}

void UndoStack::pop()
{
    if (!s.empty())
        s.pop();
}

ActionLog UndoStack::top()
{
    return s.top();
}

bool UndoStack::empty()
{
    return s.empty();
}

size_t UndoStack::size()
{
    return s.size();
}
