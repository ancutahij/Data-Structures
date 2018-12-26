#include<stdio.h>
#include<malloc.h>
#include "cchashtable.h"
#include "common.h"

#define HT_DEFAULT_SIZE 13

int HtCreate(CC_HASH_TABLE** HashTable)
{
	//printf("1. %d 2.%d", sizeof(CC_NODE*), sizeof(CC_NODE));
	if (HashTable == NULL)
	{
		return -1;
	}
	*HashTable = (CC_HASH_TABLE*)malloc(sizeof(CC_HASH_TABLE));
	if (*HtHasKey == NULL)
	{
		return -1;
	}

	(*HashTable)->Count = 0;
	(*HashTable)->Size = HT_DEFAULT_SIZE;
	(*HashTable)->Items = malloc(sizeof(CC_NODE *)* HT_DEFAULT_SIZE); // a matrix with a row and multiple columns
	// a column starts with a pointer to a node
	//*((*HashTable)->Items) = malloc(sizeof(CC_NODE) *HT_DEFAULT_SIZE);

	if ((*HashTable)->Items == NULL)
	{
		free(*HashTable);
		return -1;
	}
	int i = 0;
	CC_NODE** dynamicVector = (*HashTable)->Items;
	for (; i < HT_DEFAULT_SIZE; i++)
	{
		//((*HashTable)->Items)[i] = NULL;
		dynamicVector[i] = NULL;
	}
    return 0;
}

int HtDestroy(CC_HASH_TABLE** HashTable)
{
	if (HashTable == NULL || *HashTable == NULL)
	{
		return -1;
	}
	/*if (HtClear(*HashTable) == -1)
	{
		return -1;
	}
	*/

	HtClear(*HashTable);
	free(*HashTable);
    return 0;
}

static unsigned long HTHash(char *str) {
	unsigned long hash = 5381;
	int c;
	while (c = *str++)
		hash = ((hash << 5) + hash) ^ c; /* hash * 33 ^ c */
	return hash;
}

static unsigned int HTHashFunction(char *str, CC_HASH_TABLE * HashTable) {
	return HTHash(str) % HashTable->Size;
}


int HTResizeHashTable(CC_HASH_TABLE* HashTable, int value) 
{
	if (value < HT_DEFAULT_SIZE)
	{
		return 0; // we can't reduce the size of hash table below the minimum
	}

	int primeSize = NextPrime(value); // get the next prime value

	

	// create a deep copy of initial HashTable, except of elements array 
	CC_HASH_TABLE * replicateHT = NULL;
	HtCreate(&replicateHT);
	replicateHT->Count = HashTable->Count;
	replicateHT->Size= HashTable->Size;
	free(replicateHT->Items);
	replicateHT->Items = NULL;


	CC_NODE** dynamicVector = malloc(sizeof(CC_NODE *)* primeSize);
	if (dynamicVector == NULL)
	{
		return -1;
	}
	int i = 0;
	for (; i < primeSize; i++)
	{
		dynamicVector[i] = NULL;
	}


	//switch of elements arrays
	//Initial HashTable gets an empty array whose linked lists point to NULL. Also size and count variables are changed
	//replicateHT gets the old array
	CC_NODE** existingDynamicVector = HashTable->Items;
	HashTable->Items = dynamicVector;
	HashTable->Count = 0;
	HashTable->Size = primeSize;
	replicateHT->Items = existingDynamicVector;

	// All old elements are put back in HashTable, but in different locations
	i = 0;
	for (; i < replicateHT->Size; i++)
	{
		CC_NODE* headList = existingDynamicVector[i];
		while (headList != NULL)
		{
			
			HtSetKeyValue(HashTable, headList->Key, headList->Value);
			headList = headList->next;
		}

	}
	HtDestroy(&replicateHT);
	return 0;
}

static int HTResizeUp(CC_HASH_TABLE* HashTable) {
	const int new_size = HashTable->Size * 2;
	return HTResizeHashTable(HashTable, new_size);
}



static int HTResizeDown(CC_HASH_TABLE* HashTable) {
	const int new_size = HashTable->Size / 2;
	return HTResizeHashTable(HashTable, new_size);
}



int HtSetKeyValue(CC_HASH_TABLE* HashTable, char* Key, int Value)
{
	if (HashTable == NULL || Key == NULL)
	{
		return -1;
	}

	const int loadFactor = (HashTable->Count * 100) / HashTable->Size;
	if (loadFactor > 70)
	{
		if (HTResizeUp(HashTable) < 0)
			return -1; // realloc call failed
	}
	
	if (HtHasKey(HashTable, Key) == 1)
	{
		return -1;
	}
	unsigned int index = HTHashFunction(Key, HashTable);

	CC_NODE* node = malloc(sizeof(CC_NODE));
	if (node == NULL)
	{
		return -1;
	}
	node->Key = Key;
	node->Value = Value;
	node->next = NULL;

	CC_NODE** dynamicVector = HashTable->Items;
	CC_NODE* headLinkedList = dynamicVector[index];

	node->next = headLinkedList;
	dynamicVector[index]= node;
	HashTable->Count++;
	return 0;
}

int HtGetKeyValue(CC_HASH_TABLE* HashTable, char* Key, int *Value)
{
	if (HashTable == NULL || Key == NULL)
	{
		return -1;
	}

	unsigned int index = HTHashFunction(Key, HashTable);
	CC_NODE** dynamicVector = HashTable->Items;
	CC_NODE* headLinkedList = dynamicVector[index]; // initially it points to the head of linked list
	while ( headLinkedList != NULL)
	{
		//if (headLinkedList->Key == Key)
		if(string_compare(headLinkedList->Key, Key) == 0)
		{
			*Value = headLinkedList->Value;
			return 0;
		}
		headLinkedList = headLinkedList->next;
	}
	
    return 0;
}

int HtRemoveKey(CC_HASH_TABLE* HashTable, char* Key)
{
	if (HashTable == NULL || Key == NULL)
	{
		return -1;
	}

	const int loadFactor = (HashTable->Count * 100) / HashTable->Size;
	if (loadFactor <15)
	{
		if (HTResizeDown(HashTable) < 0)
			return -1; // realloc call failed
	}

	unsigned int index = HTHashFunction(Key, HashTable);
	

	CC_NODE** dynamicVector = HashTable->Items;
	CC_NODE* current = dynamicVector[index];
	CC_NODE* pre = NULL;
	if (HtHasKey(HashTable, Key) == 0)
	{
		return -1;
	}
	if (string_compare (current->Key ,Key) == 0) // we found the key on the first position
	{
		dynamicVector[index] = dynamicVector[index]->next;
		HashTable->Count--;
		free(current);
		return 0;
	}
	while (current != NULL) 
	{
		if (string_compare (current->Key , Key) == 0)
		{
			pre->next = current->next;
			free(current);
			HashTable->Count--;
			return 0;
		}
		pre = current;
		current = current->next;
	}
	return -1; 
}


static int string_compare(char* str1, char* str2)
{
	int ctr = 0;

	while (str1[ctr] == str2[ctr])
	{
		if (str1[ctr] == '\0' || str2[ctr] == '\0')
			break;
		ctr++;
	}
	if (str1[ctr] == '\0' && str2[ctr] == '\0')
		return 0;
	else
		return -1;
}
int HtHasKey(CC_HASH_TABLE* HashTable, char* Key)
{
	if (HashTable == NULL || Key == NULL)
	{
		return -1;
	}
	
	CC_NODE** dynamicVector = HashTable->Items;
	unsigned int index = HTHashFunction(Key, HashTable);
	CC_NODE* headLinkedList = dynamicVector[index];
	while (headLinkedList != NULL)
	{
		//if (headLinkedList->Key == Key)
		if (string_compare(headLinkedList->Key, Key)==0)
		{
			return 1;
		}
		headLinkedList = headLinkedList->next;
	}
    return 0; // cheia nu exista
}

int HtGetNthKey(CC_HASH_TABLE* HashTable, int Index, char** Key)
{
	if (HashTable == NULL || Key == NULL || Index >= HashTable->Count )
	{
		return -1;
	}
	int i = 0;

	CC_NODE** dynamicVector = HashTable->Items;
	for (; i < HashTable->Size && Index>=0; i++)
	{
		CC_NODE* headList = dynamicVector[i];
		while (headList != NULL)
		{
			if (Index == 0)
			{
				*Key = headList->Key;
				return 0;
			}
			Index--;
			headList = headList->next;
		}
		
	}
    return -1;
}

int HtClear(CC_HASH_TABLE* HashTable)
{
	if (HashTable->Items != NULL)
	{
		int i = 0;
		CC_NODE** dynamicVector = HashTable->Items;
		for (; i < HashTable->Size && HashTable->Count >0; i++)
		{
			//CC_NODE *tempCurent = *((*HashTable)->Items) + i; //it points to i'th bucket
			CC_NODE *tempCurent = dynamicVector[i];
			CC_NODE *tempNext = NULL;

			while (tempCurent != NULL)
			{
				tempNext = tempCurent->next; // tempNext will point to the next CC_NODE in linked list, so we can free safely the memory
				free(tempCurent);
				HashTable->Count--;
				tempCurent = tempNext;
			}
			dynamicVector[i] = NULL;

		}
		
		free(HashTable->Items);
		HashTable->Items = NULL;
		return 0;
	}
    return -1;
}

int HtGetKeyCount(CC_HASH_TABLE* HashTable)
{
	if (HashTable == NULL)
	{
		return -1;
	}
    return HashTable->Count;
}
