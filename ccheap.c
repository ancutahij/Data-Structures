#include "ccheap.h"
#include "common.h"
#include<stdlib.h>
#include<malloc.h>
#include<stdio.h>
#define HP_DEFAULT_SIZE 20
/*
	Compare 2 integers. 
	Return:		1,	first parameter>= second parameter
				0,  otherwiase
*/
static int HpCompareMaxHeap(int number1, int number2) {
	return (number1 > number2) ? 1 : 0;
}


/*
Compare 2 integers.
Return:	
	1,	first parameter < second parameter
	0,  otherwiase
*/
static int HpCompareMinHeap(int number1, int number2) {
	return (number1 < number2) ? 1 : 0;
}


static int HPGetParent(int position) 
{
	return (position - 1) / 2 ;   
}
static int HPGetLeftChild(int position)
{
	return position * 2 + 1;
}
static int HPGetRightChild(int position) {
	return position * 2 + 2;
}
/*
	Create a heap. The type of the heap is determinated by CmpFunction parameter
*/
int HPCreateHeap(CC_HEAP **Heap, CC_VECTOR* InitialElements, int (*CmpFunction)(int, int))
{
	if (Heap == NULL)
	{
		return -1;
	}
	*Heap = (CC_HEAP*)malloc(sizeof(CC_HEAP));
	if (*Heap == NULL)
	{
		return -1;
	}
	(*Heap)->CompareFunction = CmpFunction;
	(*Heap)->ActualSize = 0;

	if (InitialElements != NULL)
	{
		int initialSize = HP_DEFAULT_SIZE;
		if (initialSize < InitialElements->actualSize)
		{
			initialSize = InitialElements->actualSize;
		}
		(*Heap)->MemorySize = initialSize;
		(*Heap)->Elements = malloc(sizeof(int)*initialSize);
		if ((*Heap)->Elements == NULL)
		{
			free(*Heap);
			return -1;
		}

		int i = 0;
		for (; i < InitialElements->actualSize; i++)
		{
			HpInsert(*Heap, InitialElements->elements[i]);
		}

	}
	else
	{
		(*Heap)->MemorySize = HP_DEFAULT_SIZE;
		(*Heap)->Elements = malloc(sizeof(int)*HP_DEFAULT_SIZE);
		if ((*Heap)->Elements == NULL)
		{
			free(*Heap);
			return -1;
		}
	}
	return 0;

}
int HpCreateMaxHeap(CC_HEAP **MaxHeap, CC_VECTOR* InitialElements)
{
	return HPCreateHeap(MaxHeap, InitialElements, &HpCompareMaxHeap);

}

int HpCreateMinHeap(CC_HEAP **MinHeap, CC_VECTOR* InitialElements)
{
	return HPCreateHeap(MinHeap, InitialElements, &HpCompareMinHeap);
}

int HpDestroy(CC_HEAP **Heap)
{
	if (Heap == NULL || *Heap == NULL)
	{
		return -1;
	}
	if ((*Heap)->Elements != NULL)
	{
		free((*Heap)->Elements);
		(*Heap)->Elements = NULL;
	}
	free(*Heap);
	*Heap = NULL;
    return 0;
}


static int HpResizeHeap(CC_HEAP* Heap, int NewSize) {

	int *temp = realloc(Heap->Elements,  NewSize * sizeof(int));
	if (temp == NULL) // realloc failed
	{
		return -1;
	}
	Heap->Elements= temp;
	Heap->MemorySize = NewSize;
	return 0;
}
int HpInsert(CC_HEAP *Heap, int Value)
{
	if (Heap == NULL)
	{
		return -1;
	}
	if(Heap->ActualSize == Heap->MemorySize) // it's necessary a resize of the dynamic vector
	{
		if (HpResizeHeap(Heap, Heap->MemorySize * 2) == -1)
		{
			return -1;
		}
	}
	// initially, we insert Value at the end of the heap's vector
	//after that, we establish the Heap property if it's necessary
	int *elements = Heap->Elements;
	elements[Heap->ActualSize] = Value;
	Heap->ActualSize = Heap->ActualSize + 1;

	int pos = Heap->ActualSize - 1;
	int(* CmpFunction)(int, int)= Heap->CompareFunction;
	int parent = HPGetParent(pos);
	while (pos > 0 && CmpFunction(elements[parent], elements[pos])==0)
	{
		SwapFunction(&elements[parent], &elements[pos]);
		pos = parent ;
		parent = HPGetParent(pos);
	}

	
    return 0;
}

int HpRemove(CC_HEAP *Heap, int Value)
{
	if (Heap == NULL)
	{
		return -1;
	}

	// if the heap type is the minimum one and min value(extreme value) is bigger than Value parameter, it's not necessary to iterate through heap elements
	// because there is no element equal to Value
	// same for max Heap 
	int *elems = Heap->Elements;
	if (Heap->CompareFunction(Value, elems[0]) == 1)
	{
		return 0;
	}


	CC_VECTOR *vectorDinamic;
	if (VecCreate(&vectorDinamic) == -1)
	{
		return -1;
	}
		
	int temp;
	int retValue = HpRemovePeek(Heap, &temp);
	if (retValue == -1) // the heap doesn't contain any element
	{
		return 0;
	}
	

	int stopFlag = 0;
	while (temp != Value && !stopFlag) // 
	{
	

		VecInsertTail(vectorDinamic, temp);
		HpRemovePeek(Heap, &temp);
		

		if (Heap->CompareFunction(Value, elems[0]) == 1) // eg for MinHeap: Extreme value is strictly bigger than Value parameter
														// it's not necessary to continue looking for Value Parameter bc it doesn't exist in this heap
		{
			stopFlag=1;
		}
	}


	if (temp == Value)  //  delete all elements that are equal to Value
	{
		//HpPopExtreme(Heap, temp);
		HpPopExtreme(Heap, &temp);
	}
	//inserts the elements from the dynamic vector , back into our heap according to heap property
	int i = 0;
	for (; i < vectorDinamic->actualSize; i++)
	{
		HpInsert(Heap, vectorDinamic->elements[i]);
	}

	//free memory of dynamic vector
	VecDestroy(&vectorDinamic);
	return 0;
}



/*
	Remove the extreme value only one time. 
	eg:   1
		/	\
		1	2
	result:		 1
				/
			   2
*/
static int  HpRemovePeek(CC_HEAP *Heap, int *ExtremeValue)
{
	if (Heap->ActualSize == 0)
	{
		return -1;
	}
	int *elements = Heap->Elements;
	*ExtremeValue = elements[0];
	Heap->ActualSize = Heap->ActualSize - 1;
	elements[0] = elements[Heap->ActualSize];
	
	int pos = 0;
	int stopFlag = 0;
	int(*CmpFunction)(int, int) = Heap->CompareFunction;
	while (stopFlag == 0)
	{
		int posLeftChild = HPGetLeftChild(pos);
		int posRightChild = HPGetRightChild(pos);
		/*
		// a parent has 2 children and both of its children doesn't respect heap property
		 min heap:	10
					/ \
				   1   -1
		In this case we have to choose the smallest one children
		Both of children can become parents!
		*/
		if (posRightChild < Heap->ActualSize && CmpFunction(elements[pos], elements[posLeftChild]) == 0 && CmpFunction(elements[pos], elements[posRightChild]) == 0)
		{
			if (CmpFunction(elements[posRightChild], elements[posLeftChild]) == 1)  // -1 < 1 -> 1
			{
				SwapFunction(&elements[pos], &elements[posRightChild]);
				pos = posRightChild;
			}
			else
			{
				SwapFunction(&elements[pos], &elements[posLeftChild]);
				pos = posLeftChild;
			}
		}
		else
		{
			// only one children of two can become parent
			if (posLeftChild <Heap->ActualSize && CmpFunction(elements[pos], elements[posLeftChild]) == 0) // swap between parent and left child
			{
				SwapFunction(&elements[pos], &elements[posLeftChild]);
				pos = posLeftChild;
			}
			else
			{
				if (posRightChild < Heap->ActualSize && CmpFunction(elements[pos], elements[posRightChild]) == 0) // swap between parent and right child
				{
					SwapFunction(&elements[pos], &elements[posRightChild]);
					pos = posRightChild;
				}
				else
					// no one of the children can become parent or there are no children
				{
					stopFlag = 1; // we established the heap property back
				}
			}
		}
	
	}
	return 0;
}

int HpGetExtreme(CC_HEAP *Heap, int* ExtremeValue)
{
	if (Heap == NULL)
	{
		return -1;
	}
	*ExtremeValue = Heap->Elements[0];
    return 0;
}

int HpPopExtreme(CC_HEAP *Heap, int* ExtremeValue)
{
	if (Heap == NULL)
	{
		return -1;
	}
	HpGetExtreme(Heap, ExtremeValue);

	if (Heap->ActualSize == 1)
	{
		Heap->ActualSize--;
		return 0;
	}

	int temp;
	HpRemovePeek(Heap, &temp);
	while (temp == Heap->Elements[0]) // delete all elements that are equal to Value
	{
		HpRemovePeek(Heap, &temp);
	}
    return 0;
}

int HpGetElementCount(CC_HEAP *Heap)
{
	if (Heap == NULL)
	{
		return -1;
	}
    return Heap->ActualSize;
}


/*
	Get Type of Heap
	Returns -1 if the Heap is a Min Heap
	Returns 1 if the Heap is a Max Heap
	Return 0 if all elementes are equal
 
*/
static int HpGetTypeHeap(CC_HEAP* Heap)
{

	int posStart = 0;
	int leftChild = HPGetLeftChild(posStart);
	int rightChild = HPGetRightChild(posStart);
	int * elements = Heap->Elements;
	while (leftChild < Heap->ActualSize) // while this node has atleast one child
	{
		if (elements[leftChild] < elements[posStart])
		{
			return 1;
		}
		else
		{
			if (elements[leftChild] > elements[posStart])
			{
				return -1;
			}

		}
		if (rightChild < Heap->ActualSize)
		{
			if (elements[rightChild] < elements[posStart])
			{
				return 1;
			}
			else
			{
				if (elements[rightChild] > elements[posStart])
				{
					return -1;
				}

			}
			
		}
		posStart++;
		leftChild = HPGetLeftChild(posStart);
		rightChild = HPGetRightChild(posStart);

	}
	return 2;
}


int HpSortToVector(CC_HEAP *Heap, CC_VECTOR* SortedVector)
{
	if (Heap == NULL || SortedVector == NULL)
	{
		return -1;
	}
	if (SortedVector->actualSize != 0) // our vector already contains some elements which have to be also sorted
	{
		int i = 0;
		for (; i < SortedVector->actualSize; i++)
		{
			HpInsert(Heap, SortedVector->elements[i]);
		}
		VecClear(SortedVector); // Now, SortedVector has no elements.
	}

	// identify the type of the heap 
	int type = HpGetTypeHeap(Heap);
	switch (type)
	{
	case 2: // all elements are equal => complexity Theta(n)
	{	
		int i = 0;
		int *elements = Heap->Elements;
		for (; i < Heap->ActualSize; i++)
		{
			VecInsertTail(SortedVector, elements[i]);
		}
	}
		break;
	case -1: // Heap is a Min Heap. We will extract the extreme value and we insert it at the end of SortedVector. Complexity Theta( n logn)
	{
		while (Heap->ActualSize > 0)
		{
			int temp;
			HpRemovePeek(Heap, &temp);
			VecInsertTail(SortedVector, temp);
		}
	}
		break;
	default:// Maxheap. We will increase the actual size of the vector to the actual size of heap.
			//We will extract the extreme value and we insert it from the end to the beginning in vector
			// Complexity Theta(n log n)
	{
		int i = 0;
		for (; i < Heap->ActualSize; i++)
		{
			VecInsertTail(SortedVector, -1);
		}
		while (Heap->ActualSize > 0)
		{
			int temp;
			HpRemovePeek(Heap, &temp);
			//VecInsertTail(SortedVector, temp);
			SortedVector->elements[Heap->ActualSize ] = temp;
		}
	}
		break;
	}
    return 0;
}
