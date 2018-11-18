#include "ccstack.h"
#include "common.h"
#include<stdio.h>
#include<malloc.h>

int StCreate(CC_STACK **Stack)
{
	if (*Stack != NULL)
	{
		return -1;
	}
	*Stack = malloc(sizeof(CC_STACK));
	if (*Stack == NULL)
	{
		return -1;
	}
	(*Stack)->peek = NULL;   // create an empty stack where the first element points to NULL
	return 0;
}

int StDestroy(CC_STACK **Stack)
{
	if (Stack == NULL)
	{
		return -1;
	}

	if (*Stack == NULL)
	{
		return -1;
	}

	if ((*Stack)->peek != NULL)
	{
		StDestroyRecursively(&(*Stack)->peek);
	}
	free(*Stack);
    return 0;
}

void StDestroyRecursively(CC_STACK_NODE** NodeStart) {
	if ((*NodeStart)->next != NULL)
	{
		StDestroyRecursively(&(*NodeStart)->next);
	}
	free(*NodeStart);
	*NodeStart = NULL;
}

int StPush(CC_STACK *Stack, int Value)
{
	if (Stack == NULL)
	{
		return -1;
	}
	CC_STACK_NODE *newNode = malloc(sizeof(CC_STACK_NODE));
	if (newNode == NULL) // cannot allocate memory for creating a new node
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
	if (Stack == NULL)
	{
		return -1;
	}
	if (Stack->peek == NULL) // The stack doesn't contain any node.
	{
		return -1;
	}
	*Value = Stack->peek->info;
	CC_STACK_NODE* temp = Stack->peek;
	Stack->peek = Stack->peek->next;
	free(temp);
    return 0;
}

int StPeek(CC_STACK *Stack, int *Value)
{
	if (Stack == NULL)
	{
		return -1;
	}
	if (Stack->peek == NULL) // The stack doesn't contain any node.
	{
		return -1;
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
	StDestroyRecursively(&(Stack->peek));
    return 0;
}

int StPushStack(CC_STACK *Stack, CC_STACK *StackToPush)
{
	if (Stack == NULL && StackToPush == NULL)
	{
		return -1;
	}
	if (StackToPush->peek == NULL) // there are no elements into StacktoPush Stack, so Stack stack is equal to initial Stack stack
	{
		return 0;
	}
	
	// create a new stack that will contain the elements of StacktoPush in a reverse order
	CC_STACK* tempStack = NULL;
	StCreate(&tempStack);
	while (StackToPush->peek != NULL)
	{
		int poppedValue;
		int retValue=0; // check if StPop and StPush functions doesn't crash
		retValue = StPop(StackToPush, &poppedValue);
		if (retValue != 0)
		{
			return -1;
		}
		retValue = StPush(tempStack, poppedValue);
		if (retValue != 0)
		{
			return -1;
		}

	}

	// pop all values from tempStack and push them into Stack
	while (tempStack->peek != NULL)
	{
		int poppedValue;
		int retValue = 0; // check if StPop and StPush functions doesn't crash
		retValue =StPop(tempStack, &poppedValue);
		if (retValue != 0)
		{
			return -1;
		}
		retValue =StPush(Stack, poppedValue);
		if (retValue != 0)
		{
			return -1;
		}
	}
    return 0;
}
