#ifndef NODE_H
#define NODE_H

#include "BaseEvent.h"
struct Node {
    BaseEvent* data;
    Node* next;
    Node(BaseEvent* item) : data(item), next(nullptr) {}
};

#endif