#ifndef NODE_H
#define NODE_H
#include "shiptype.h"
struct Node
{
    Ship *value;
    Node *next;
};
#endif