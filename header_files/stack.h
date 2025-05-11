#ifndef STACK_H
#define STACK_H

#include "directions.h"

typedef struct{
    int x;
    int y;
    Direction d;
} StackNode;

typedef struct{
    StackNode *stack;
    int top;
} Stack;

#endif