#include"ccqueue.h"

#include<stdlib.h>
#include<malloc.h>
#include<stdio.h>

int QCreate(CC_QUEUE **Queue)
{
	if (Queue == NULL)
	{
		return -1;
	}

	*Queue = malloc(sizeof(CC_QUEUE));
	if (*Queue == NULL)
	{
		return -1;
	}

	(*Queue)->front = NULL;
	(*Queue)->back= NULL;

	return 0;
}


int QDestroy(CC_QUEUE **Queue)
{
	if (Queue == NULL)
	{
		return -1;
	}

	if (*Queue== NULL)
	{
		return -1;
	}

	while (QIsEmpty(*Queue) == 0)
	{
		void* tempValue;
		//STPush(*Queue, &tempValue);
		QPop(*Queue, &tempValue);
		printf("aici");
	}
	free(*Queue);
	*Queue = NULL;
	return 0;
}


int QIsEmpty(CC_QUEUE *Queue) {
	if (Queue == NULL)
	{
		return -1;
	}
	if (Queue->front == NULL)
	{
		return 1;
	}
	return 0;
}

// pop out the first element of queuu
int QPop(CC_QUEUE *Queue, ElemType* Value) {
	if (Queue == NULL || Value == NULL)
	{
		return -1;
	}
	if (Queue->front == NULL)
	{
		return -1;
	}
	CC_QUEUE_NODE * temp = Queue->front;
	*Value = temp->info;
	Queue->front = Queue->front->next;
	free(temp);
	return 0;
}


int QPush(CC_QUEUE *Queue, ElemType el) {
	if (Queue == NULL)
	{
		return -1;
	}

	if (Queue->front == NULL)
	{
		CC_QUEUE_NODE * node = malloc(sizeof(CC_QUEUE_NODE));
		if (node == NULL)
		{
			return -1;
		}
		(node->info) = el;
		node->next = NULL;
		node->pre = NULL;
		Queue->front = node;
		Queue->back = node;
		return 0;
		
	}

	CC_QUEUE_NODE * node = malloc(sizeof(CC_QUEUE_NODE));
	if (node == NULL)
	{
		return -1;
	}

	node->info = el;
	node->next = NULL;
	node->pre = Queue->back;
	Queue->back->next = node;
	Queue->back= node;
	return 0;
}

int QSize(CC_QUEUE *Queue) {
	if (Queue == NULL)
	{
		return -1;
	}
	int count = 0;
	CC_QUEUE_NODE *n = Queue->front;
	while (n != NULL)
	{
		count++;
		n = n->next;
	}
	return count;
}