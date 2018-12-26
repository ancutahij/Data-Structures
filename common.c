#include"common.h"

void SwapFunction(int *element1, int *element2)
{
	*element1 = *element1 ^ *element2;
	*element2 = *element1^ *element2;
	*element1 = *element1 ^ *element2;
}


void quickSort(int arr[], int low, int high)
{
	if (low < high)
	{

		int pi = partition(arr, low, high);
		quickSort(arr, low, pi - 1);
		quickSort(arr, pi + 1, high);
	}
}

int partition(int arr[], int low, int high)
{
	int pivot = arr[high];    // pivot 
	int i = (low - 1);

	for (int j = low; j <= high - 1; j++)
	{
		if (arr[j] <= pivot)
		{
			i++;
			SwapFunction(&arr[i], &arr[j]);
		}
	}
	SwapFunction(&arr[i + 1], &arr[high]);
	return (i + 1);
}


int IsPrime(const int numar) {
	if (numar < 2) 
	{
		return -1;
	}
	if (numar<=3)
	{
		return 1;
	}
	if (numar % 2 == 0 || numar % 3 == 0)
	{
		return -1;
	}
	int divizor= 5;
	while (divizor*divizor <= numar)
	{
		if (numar % divizor == 0 || numar % (divizor + 2) == 0) {
			return 0;
		}
		divizor += 6;
	}
	return 1;
}


/*
* Return the next prime element after number
*/
int NextPrime(int number) {
	while (IsPrime(number) != 1) {
		number++;
	}
	return number;
}