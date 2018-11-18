#include<stdio.h>
#include<malloc.h>
#include "ccvector.h"
#include "common.h"

#define VEC_DEFAULT_SIZE 4
int VecCreate(CC_VECTOR **Vector)
{
	// Vector parameter has already an address memory.
    if (*Vector != NULL)
	{
		return -1;
	}

	*Vector = malloc(sizeof(CC_VECTOR));
	if (Vector == NULL) 
	{
		return -1;
	}

	(*Vector)->memorySize = VEC_DEFAULT_SIZE;
	(*Vector)->actualSize = 0;
	(*Vector)->elements = malloc(sizeof(int) * VEC_DEFAULT_SIZE);
	if ((*Vector)->elements == NULL)
	{
		free(Vector);
		*Vector = NULL;
		return -1;
	}
	return 0;
}

int VecDestroy(CC_VECTOR **Vector)
{
	if (Vector == NULL) 
	{
		return -1;
	}

	if (*Vector == NULL)
	{
		return -1;
	}
	free((*Vector)->elements);
	free(*Vector);
	*Vector = NULL;
    return 0;
}


int VecInsertTail(CC_VECTOR *Vector, int Value)
{
	if (Vector == NULL || Vector->elements == NULL ) 
	{
		return -1;
	}
	
	int currentSize = Vector->actualSize;

	if (currentSize== Vector->memorySize) 
	{
		int *temp = realloc(Vector->elements, currentSize * 2 * sizeof(int));
		if (temp == NULL)
		{
			return -1;
		}
		Vector->elements = temp;
		Vector->memorySize = 2 * currentSize;
	}

	int *arr = Vector->elements;
	arr[currentSize] = Value;
	Vector->actualSize = currentSize + 1;

    return 0;
}

int VecInsertHead(CC_VECTOR *Vector, int Value)
{
	if (Vector == NULL || Vector->elements == NULL) 
	{
		return -1;
	}
	
	int currentSize = Vector->actualSize;
	if (currentSize >= Vector->memorySize) {
		int *temp = realloc(Vector->elements,( currentSize * 2 )* sizeof(int));
		if (temp == NULL) 
		{
			return -1;
		}
		Vector->elements = temp;
		Vector->memorySize = 2 * currentSize;
	}

	int i = currentSize;
	int *arr = Vector->elements;
	for (; i > 0; i--) 
	{
		arr[i ] = arr[i-1];
	}
	arr[0] = Value;
	Vector->actualSize = currentSize + 1;

    return 0;
}

int VecInsertAfterIndex(CC_VECTOR *Vector, int Index, int Value)
{
	// in case that the Vector pointer points to a NULL adddress or the vector of elements points to a NULL address
	if (Vector == NULL || Vector->elements==NULL) 
	{
		return -1;
	}
	int currentSize = Vector->actualSize;
	if (currentSize >= Vector->memorySize)
	{
		int *temp = realloc(Vector->elements, (currentSize * 2) * sizeof(int));
		if (temp == NULL)
		{
			return -1;
		}
		Vector->elements = temp;
		Vector->memorySize = 2 * currentSize;
	}


	int i = currentSize;
	int *arr = Vector->elements;

	for (; i > Index+1 ; i--) 
	{
		arr[i] = arr[i - 1];

	}
	arr[Index+1] = Value;
	Vector->actualSize = currentSize + 1;

    return 0;
}

int VecRemoveByIndex(CC_VECTOR *Vector, int Index)
{
	if (Vector == NULL || Vector->elements == NULL)
	{
		return-1;
	}

	int i = Index;
	int currentSize = Vector->actualSize;
	int *arr = Vector->elements;
	for (; i < currentSize; i++)
	{
		arr[i] = arr[i + 1];
	}
	Vector->actualSize = currentSize - 1;

	if (Vector->actualSize <= (Vector->memorySize / 4))
	{
		int *temp = realloc(Vector->elements, sizeof(int) * (Vector->memorySize / 2));
		if (temp == NULL)
		{
			return -1;
		}
		Vector->elements = temp;
	}
    return 0;
}

int VecGetValueByIndex(CC_VECTOR *Vector, int Index, int *Value)
{
	if (Vector == NULL || Vector->elements == NULL)
	{
		return-1;
	}
	if (Index < 0)
	{
		return -1;
	}

	int currentSize = Vector->actualSize;
	if (currentSize <= Index)
	{
		return -1;
	}

	int *arr = Vector->elements;
	*Value = arr[Index];
    return 0;
}

int VecGetCount(CC_VECTOR *Vector)
{
	if (Vector == NULL || Vector->elements == NULL)
	{
		return -1;
	}
	
	int currentSize = Vector->actualSize;
	return currentSize;
}

int VecClear(CC_VECTOR *Vector)
{
	if (Vector == NULL || Vector->elements == NULL)
	{
		return -1;
	}
	free(Vector->elements);
	Vector->elements = malloc(sizeof(int) * VEC_DEFAULT_SIZE);
	Vector->actualSize = 0;
	Vector->memorySize = VEC_DEFAULT_SIZE;
    return 0;
}


/*
	The function makes use of quick sort method in order to sort the list of elements
*/
int VecSort(CC_VECTOR *Vector)
{
	if (Vector == NULL || Vector->elements == NULL)
	{
		return -1;
	}
	int currentSize = Vector->actualSize;
	int *arr= Vector->elements;
	if (currentSize > 1)
	{
		quickSort(arr, 0, currentSize);
	}
	return 0;
}


