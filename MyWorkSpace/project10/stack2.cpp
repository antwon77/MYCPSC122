#ifndef STACK_H
#define STACK_H

#include "list.h"

class Stack : public List
{
public:
    // Constructor: Initializes the stack
    Stack();

    // Pushes an item onto the top of the stack
    void Push(itemType newItem);

    // Removes the top item from the stack
    void Pop();

    // Returns the top item from the stack without removing it
    itemType Peek();
};

#endif


