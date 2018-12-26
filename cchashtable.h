#pragma once



typedef struct _CC_NODE {
	char *Key;
	int Value;
	struct _CC_NODE *next;
} CC_NODE;

typedef struct _CC_HASH_TABLE { 
	int Size; // number of buckets
	int Count; // number of elements
	CC_NODE** Items;  // a matrix consisted of only one row and multiple columns
} CC_HASH_TABLE; 
  

int HtCreate(CC_HASH_TABLE** HashTable); 
int HtDestroy(CC_HASH_TABLE** HashTable); 
 //introducem o cheie noua, daca exista cheia return -1
static unsigned long HTHash(char *str);
static unsigned int HTHashFunction(char *str, CC_HASH_TABLE * HashTable);
static int HTResizeHashTable(CC_HASH_TABLE* HashTable, int value);
static int string_compare(char* str1, char* str2);

int HtSetKeyValue(CC_HASH_TABLE* HashTable, char* Key, int Value); 
int HtGetKeyValue(CC_HASH_TABLE* HashTable, char* Key, int *Value); 
int HtRemoveKey(CC_HASH_TABLE* HashTable, char* Key); 
int HtHasKey(CC_HASH_TABLE* HashTable, char* Key); 
// trebuie sa returneze a n-a cheie
int HtGetNthKey(CC_HASH_TABLE* HashTable, int Index, char** Key); 
int HtClear(CC_HASH_TABLE* HashTable); 
int HtGetKeyCount(CC_HASH_TABLE* HashTable);  
