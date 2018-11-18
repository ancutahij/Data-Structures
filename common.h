#pragma once

#define CC_UNREFERENCED_PARAMETER(X) X

void SwapFunction(int *element1, int *element2)
{
	*element1 = *element1 ^ *element2;
	*element2 = *element1^ *element2;
	*element1 = *element1 ^ *element2;
}