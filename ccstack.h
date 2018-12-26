#pragma once

typedef void* TypeElem;

typedef struct _CC_STACK_NODE {
	int info;
	struct _CC_STACK_NODE *next;
} CC_STACK_NODE;

typedef struct _CC_STACK{ 
	CC_STACK_NODE *peek;
} CC_STACK, *CC_PSTACK; 
  
int StCreate(CC_STACK **Stack);
int StDestroy(CC_STACK **Stack);
 
int StPush(CC_STACK *Stack, int Value);
int StPop(CC_STACK *Stack, int *Value);
int StPeek(CC_STACK *Stack, int *Value); // gets top of stack without popping the value
int StIsEmpty(CC_STACK *Stack); // returns 1 if stack is empty and 0 otherwise
int StGetCount(CC_STACK *Stack); // returns the number of elements in the stack
int StClear(CC_STACK *Stack); // removes all elements from the stack

static int StPopPushStack(CC_STACK *PopStack, CC_STACK *PushStack); // move all elements from PopStack stack into PushStack stack
// StPushStack removes all the elements from the StackToPush and appends 
// them to the first stack 
// ex: Stack1: 1, 2, 3
//     Stack2: 1, 4, 5
// After push: Stack1: 1, 2, 3, 1, 4, 5
//             Stack2: empty
int StPushStack(CC_STACK *Stack, CC_STACK *StackToPush); 
