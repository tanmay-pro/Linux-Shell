// Created by tanmaypro on 9/16/21.
#ifndef GOYSHELL_QUEUE_H
#define GOYSHELL_QUEUE_H

#include "function_def.h"

typedef char* elementtype;
typedef struct node node;
typedef struct node *ptrnode;

struct node
{
	elementtype data;
	ptrnode next;
	ptrnode rear;
	ptrnode prev;
};

void push_front(ptrnode p, elementtype data); // Insert at front
ptrnode createnode(elementtype data);
void pop(ptrnode p);                         // Remove from front
void push_back(ptrnode p, elementtype data); // Insert at Rear
void eject(ptrnode p);                       // Remove item from rear
bool empty(ptrnode p);                       // Return whether the Queue is empty or not
int size(ptrnode p);                         // Return The size of Queue
elementtype front(ptrnode p);                // Return the first element of the queue
elementtype back(ptrnode p);                 // Return the last element of the queue


#endif //GOYSHELL_QUEUE_H
