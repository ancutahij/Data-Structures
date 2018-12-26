#pragma once



typedef void* ElemType;

typedef struct _CC_QUEUE_NODE {
	ElemType info;
	struct _CC_QUEUE_NODE *next;
	struct _CC_QUEUE_NODE *pre;

} CC_QUEUE_NODE;

typedef struct _CC_QUEUE {
	CC_QUEUE_NODE *front, *back;
} CC_QUEUE;



int QCreate(CC_QUEUE **Queue);
int QDestroy(CC_QUEUE **Queue);


int QPush(CC_QUEUE *Queue, ElemType el);
int QPop(CC_QUEUE *Queue, ElemType* Value);
int QIsEmpty(CC_QUEUE *Queue); // returns 1 if queue is empty and 0 otherwise
int QSize(CC_QUEUE *Queue); 

