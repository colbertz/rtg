#include <iostream>
#include <stdlib.h>
#include <time.h>   
#include "assert.h" 

#define MIN 0       
#define MAX 999  

#define Random(x) (rand() % x)

// xor swap is actually slower than the normal swap
// Not a pratical one.
void xor_swap(int& a, int& b)
{
	// the xor swap can not handle both a and b 
	// points to the same address. 
	//In that case, it resets the memory to 0;
    if (&a == &b) return;
	a ^= b;
	b ^= a;
	a ^= b;
}

void normal_swap(int& a, int& b)
{
	int temp(a);
	a = b;
	b = temp;
}

void quicksort(int* data, int start, int end)
{
	if (start >= end) return;

	// we can randomly pick up a pivot instead of
	// always using the first item to avoid sorting
	// a sorted array, which gives the badest 
	// performance expectaion.
	int pivot = data[start];

	int i = start;
	int j = end;

	while (i<j)
	{
		i++;
		while (data[j]>pivot) j--;
		while (data[i]<pivot) i++;

		if (i >= j) break;

		normal_swap(data[i], data[j]);
	}

	normal_swap(data[start], data[j]);

	quicksort(data, start, j - 1);
	quicksort(data, j + 1, end);
}

int main()
{
	srand((unsigned)time(NULL));

	int array[100];
	int n = 100;
	while (n--)
	{
		array[n] = MIN + rand() % (MAX + MIN - 1);
	}

	quicksort(array, 0, 99);
	
	n = 100;
	while (n--)
	{
		if (n > 0) assert(array[n] >= array[n - 1]);

		std::cout << array[n] << std::endl;
	}
}