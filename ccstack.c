#include "ccstack.h"
#include "common.h"
#include<stdio.h>
#include<malloc.h>

int StCreate(CC_STACK **Stack)
{
	if (*Stack != NULL || Stack==NULL)
	{
		return -1;
	}
	*Stack = (CC_STACK *)malloc(sizeof(CC_STACK));
	if (*Stack == NULL)
	{
		return -1;
	}
	(*Stack)->peek = NULL;   // create an empty stack where the first element points to NULL
	return 0;
}

int StDestroy(CC_STACK **Stack)
{
	if (Stack == NULL|| *Stack == NULL)
	{
		return -1;
	}


	while (StIsEmpty(*Stack) == 0)
	{
		int tempValue;
		StPop(*Stack, &tempValue);
	}
	free(*Stack);
    return 0;
}



int StPush(CC_STACK* Stack, int Value)
{
	if (Stack == NULL)
	{
		return -1;
	}
	CC_STACK_NODE *newNode =(CC_STACK_NODE *) malloc(sizeof(CC_STACK_NODE));
	if (newNode == NULL) // cannot allocate new memory for creating a node
	{
		return -1;
	}
	newNode->info = Value;
	newNode->next = Stack->peek;
	Stack->peek = newNode;
    return 0;
}

int StPop(CC_STACK *Stack, int *Value)
{
	if (Stack == NULL || Value == NULL)
	{
		return -1;
	}
	if (StIsEmpty(Stack) == 1) // The stack doesn't contain any node.
	{
		return 0;
	}
	*Value = Stack->peek->info;
	CC_STACK_NODE* temp = Stack->peek;
	Stack->peek = Stack->peek->next;
	free(temp);
    return 0;
}

int StPeek(CC_STACK *Stack, int *Value)
{
	if (Stack == NULL || Value== NULL)
	{
		return -1;
	}
	if (StIsEmpty(Stack) == 1 ) // The stack doesn't contain any node.
	{
		return 0;
	}
	*Value = Stack->peek->info;
    return 0;
}

int StIsEmpty(CC_STACK *Stack)
{
	if (Stack == NULL)
	{
		return -1;
	}
	if (Stack->peek == NULL)
	{
		return 1;
	}
	return 0;
}

int StGetCount(CC_STACK *Stack)
{
	if (Stack == NULL)
	{
		return -1;
	}
	int counter = 0;
	CC_STACK_NODE *temp = Stack->peek;
	while (temp != NULL)
	{
		counter = counter + 1;
		temp = temp->next;
	}
	return counter;
}

int StClear(CC_STACK *Stack)
{
	if (Stack == NULL)
	{
		return -1;
	}
	
	while (StIsEmpty(Stack) == 0)
	{
		int tempValue;
		StPop(Stack, &tempValue);
	}
    return 0;
}

static int StPopPushStack(CC_STACK *PopStack, CC_STACK *PushStack)
{
	// it's not necessary to check validaty of parameters bc this is a static function which is used only in this module
	while (StIsEmpty(PopStack) == 0)
	{
		int poppedValue;
		int retValue = 0; // check if StPop and StPush functions doesn't crash
		retValue = StPop(PopStack, &poppedValue);
		if (retValue != 0)
		{
			return -1;
		}
		retValue = StPush(PushStack, poppedValue);
		if (retValue != 0)
		{
			return -1;
		}

	}
	return 0;
}
int StPushStack(CC_STACK *Stack, CC_STACK *StackToPush)
{
	if (Stack == NULL && StackToPush == NULL)
	{
		return -1;
	}
	// in case that the StackToPush is empty, the final result will be the initial Stack because there are no elements to be added
	if (StIsEmpty(StackToPush) == 1)
	{
		return 0;
	}
	// create a new stack that will contain the elements of Stack stack in a reverse order
	CC_STACK* tempStack = NULL;
	StCreate(&tempStack);
	StPopPushStack(Stack, tempStack);

	// create a new stack that will contain the elements of StaclToPush stack in a reverse order
	CC_STACK* tempStack2 = NULL;
	StCreate(&tempStack2);
	StPopPushStack(StackToPush, tempStack2);


	//push elements back to Stack
	StPopPushStack(tempStack2, Stack);
	StPopPushStack(tempStack, Stack);

	// destroy auxiliary stacks
	StDestroy(&tempStack);
	StDestroy(&tempStack2);

    return 0;
}
