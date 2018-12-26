#include "ccgenericstack.h"
#include "common.h"
#include<stdio.h>
#include<malloc.h>

int GenStCreate(CC_GENERIC_STACK **Stack)
{
	if (*Stack != NULL || Stack == NULL)
	{
		return -1;
	}
	*Stack = (CC_GENERIC_STACK *)malloc(sizeof(CC_GENERIC_STACK));
	if (*Stack == NULL)
	{
		return -1;
	}
	(*Stack)->peek = NULL;   // create an empty stack where the first element points to NULL
	return 0;
}

int GenStDestroy(CC_GENERIC_STACK **Stack)
{
	if (Stack == NULL)
	{
		return -1;
	}

	if (*Stack == NULL)
	{
		return -1;
	}

	while (GenStIsEmpty(*Stack) == 0)
	{
		TypeElem tempValue;
		GenStPop(*Stack, &tempValue);
	}
	free(*Stack);
	return 0;
}



int GenStPush(CC_GENERIC_STACK* Stack, TypeElem Value)
{
	if (Stack == NULL)
	{
		return -1;
	}
	CC_GENERIC_NODE *newNode = (CC_GENERIC_NODE *)malloc(sizeof(CC_GENERIC_NODE));
	if (newNode == NULL) // cannot allocate new memory for creating a node
	{
		return -1;
	}
	newNode->info = Value;
	newNode->next = Stack->peek;
	Stack->peek = newNode;
	return 0;
}

int GenStPop(CC_GENERIC_STACK *Stack, TypeElem *Value)
{
	if (Stack == NULL || Value == NULL)
	{
		return -1;
	}
	if (GenStIsEmpty(Stack) == 1) // The stack doesn't contain any node.
	{
		return -1;
	}
	*Value = Stack->peek->info;
	CC_GENERIC_NODE* temp = Stack->peek;
	Stack->peek = Stack->peek->next;
	free(temp);
	return 0;
}

int GenStPeek(CC_GENERIC_STACK *Stack, TypeElem *Value)
{
	if (Stack == NULL || Value == NULL)
	{
		return -1;
	}
	if (GenStIsEmpty(Stack) == 1) // The stack doesn't contain any node.
	{
		return -1;
	}
	*Value = Stack->peek->info;
	return 0;
}

int GenStIsEmpty(CC_GENERIC_STACK *Stack)
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

int GenStGetCount(CC_GENERIC_STACK *Stack)
{
	if (Stack == NULL)
	{
		return -1;
	}
	int counter = 0;
	CC_GENERIC_NODE *temp = Stack->peek;
	while (temp != NULL)
	{
		counter = counter + 1;
		temp = temp->next;
	}
	return counter;
}

int GenStClear(CC_GENERIC_STACK *Stack)
{
	if (Stack == NULL)
	{
		return -1;
	}

	while (GenStIsEmpty(Stack) == 0)
	{
		TypeElem tempValue;
		GenStPop(Stack, &tempValue);
	}
	return 0;
}


