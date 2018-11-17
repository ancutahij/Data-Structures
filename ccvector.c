#include<stdio.h>
#include<malloc.h>
#include "ccvector.h"
#include "common.h"

#define VEC_DEFAULT_SIZE 4
int VecCreate(CC_VECTOR **Vector)
{
	// Vector parameter has already an address memory.
    if (*Vector != NULL){
		return -1;
	}

	*Vector = malloc(sizeof(CC_VECTOR));
	if (Vector == NULL) {
		return -1;
	}

	(*Vector)->memorySize = VEC_DEFAULT_SIZE;
	(*Vector)->actualSize = 0;
	(*Vector)->elements = malloc(sizeof(int) * VEC_DEFAULT_SIZE);
	if ((*Vector)->elements == NULL) {
		free(Vector);
		return -1;
	}
	return 0;
}

int VecDestroy(CC_VECTOR **Vector)
{
	if (Vector == NULL) {
		return -1;
	}

	if (*Vector == NULL) {
		return -1;
	}
	free((*Vector)->elements);
	free(*Vector);
	*Vector = NULL;
    return 0;
}


int VecInsertTail(CC_VECTOR *Vector, int Value)
{
	if (Vector == NULL ) {
		return -1;
	}
	
	int currentSize = Vector->actualSize;

	if (currentSize== Vector->memorySize) {
		int *temp = realloc(Vector->elements, currentSize * 2 * sizeof(int));
		if (temp == NULL) {
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
    CC_UNREFERENCED_PARAMETER(Vector);
    CC_UNREFERENCED_PARAMETER(Value);
    return -1;
}

int VecInsertAfterIndex(CC_VECTOR *Vector, int Index, int Value)
{
    CC_UNREFERENCED_PARAMETER(Vector);
    CC_UNREFERENCED_PARAMETER(Index);
    CC_UNREFERENCED_PARAMETER(Value);
    return -1;
}

int VecRemoveByIndex(CC_VECTOR *Vector, int Index)
{
    CC_UNREFERENCED_PARAMETER(Vector);
    CC_UNREFERENCED_PARAMETER(Index);
    return -1;
}

int VecGetValueByIndex(CC_VECTOR *Vector, int Index, int *Value)
{
    CC_UNREFERENCED_PARAMETER(Vector);
    CC_UNREFERENCED_PARAMETER(Index);
    CC_UNREFERENCED_PARAMETER(Value);
    return -1;
}

int VecGetCount(CC_VECTOR *Vector)
{
    CC_UNREFERENCED_PARAMETER(Vector);
    return -1;
}

int VecClear(CC_VECTOR *Vector)
{
    CC_UNREFERENCED_PARAMETER(Vector);
    return -1;
}

int VecSort(CC_VECTOR *Vector)
{
    CC_UNREFERENCED_PARAMETER(Vector);
    return -1;
}
