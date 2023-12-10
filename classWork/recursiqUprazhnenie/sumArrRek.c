#include <stdio.h>

int sum (int *arr, int index)
{
	if(index == 0)
	{
		return arr[index];
	}
	return arr[index] + sum (arr, index - 1);
}

int main()
{

	int arr[] = {1, 2, 3, 4, 5, 10};
	int len = 6;
	printf("%d\n", sum(arr, len - 1));

	return 0;
}
