#include <stdio.h>
#include <stdlib.h>


/*
//quick sort
void swap(int *a, int *b)
{
	int c = *a;
	*a = *b;
	*b = c;
}
size_t partition(int *arr, size_t size)
{
	int pivot = arr[size / 2];
	int i = 0, j = size - 1;
	while (1)
	{
		while(arr[i] < pivot)
		{
			++i;
		}
		while (arr[j] > pivot)
		{
			--j;
		}
		if (i >= j)
			return i;
		swap(arr + i, arr + j);
	}
}

void quickSort(int *arr, size_t size)
{
	if (size <= 1) return;

	size_t pivot = partition(arr, size);
	quickSort(arr, pivot);
	quickSort(arr + pivot + 1, size - pivot - 1);
}

int main()
{

	int arr[] = {420, 5, 12, -2, 69, 42};
	int size = 6;
	quickSort(arr, size);
	for(int i = 0; i < size; ++i)
	{
		printf("%d ", arr[i]);
	}

	return 0;
}

*/

//napravi merge sort i count sort za dom



//merge sort


void merger(int *arr, int left, int mid, int right)
{
	int size1 = mid - left + 1;
	int size2 = right - mid;

	int tempLA[size1];
	int tempRA[size2];

	for(int i = 0; i < size1;  ++i)
	{
		tempLA[i] = arr[left + i];
	}
	for(int i = 0; i < size1;  ++i)
	{
		tempRA[i] = arr[mid + 1 + i];
	}


	int i = 0, j = 0;
	int mainAI = left;

	while (i < size1 && j < size2)
	{
		if(tempLA[i] <= tempRA[j])
		{
			arr[mainAI] = tempLA[i];
			++i;
		}
		else
		{
			arr[mainAI] = tempRA[j];
			++j;
		}
		++mainAI;
	}

	while (i < size1)
	{
		arr[mainAI] = tempLA[i];
		++i;
		++mainAI;
	}
	while (j < size2)
	{
		arr[mainAI] = tempRA[j];
		++j;
		++mainAI;
	}

}

void mergeSort(int *arr, int left, int right)
{
	if(left < right)
	{
		int mid =left + (right - left) / 2;
		mergeSort(arr, left, mid);
		mergeSort(arr, mid+1, right);

		merger(arr, left, mid, right);
	}
}

int main()
{

	int arr[] = {15, 2, -8, 34, 67, 50, 1, 20};
	int size = 8;
	mergeSort(arr, 0, size-1);
	for(int i = 0; i < size; ++i)
	{
		printf("%d ", arr[i]);
	}


	return 0;
}

//za syzhalenie nqma count sort v momenta :/   mozhe bi utre shte go napravq ``\_(00)_/``