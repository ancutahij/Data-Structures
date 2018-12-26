#pragma once

typedef void* TypeElem;

/*
	A simple implementation of a generic stack that accomodate all kind of elements using the void *  pointer
		
*/
typedef struct _CC_GENERIC_NODE {
	TypeElem info;
	struct  _CC_GENERIC_NODE *next;
} CC_GENERIC_NODE;

typedef struct _CC_GENERIC_STACK {
	CC_GENERIC_NODE *peek;
} CC_GENERIC_STACK;

int GenStCreate(CC_GENERIC_STACK **Stack);
int GenStDestroy(CC_GENERIC_STACK **Stack);

int GenStPush(CC_GENERIC_STACK *Stack, TypeElem Value);
int GenStPop(CC_GENERIC_STACK *Stack, TypeElem *Value);
int GenStPeek(CC_GENERIC_STACK *Stack, TypeElem *Value); // gets top of stack without popping the value
int GenStIsEmpty(CC_GENERIC_STACK *Stack); // returns 1 if stack is empty and 0 otherwise
int GenStGetCount(CC_GENERIC_STACK *Stack); // returns the number of elements in the stack
int GenStClear(CC_GENERIC_STACK *Stack); // removes all elements from the stack

