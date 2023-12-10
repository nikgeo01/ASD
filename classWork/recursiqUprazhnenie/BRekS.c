#include <stdio.h>

int search(int *arr, int left, int right, int value)
{

	if(left <= right)
	{
		int mid = (left + right) / 2;
		if(arr[mid] == value)
		{
			return 1;
		}
		int found1 = 0, found2 = 0;
		if(arr[mid] > value)
		{
			found1 = search(arr, left, mid - 1, value);
		}
		if(arr[mid] < value)
		{
			found2 = search(arr, mid + 1, right, value);
		}
		if(found1 || found2)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	return 0;
}

int main()
{

	int arr[] = {1, 3, 8, 12, 17, 26};
	int len = 6;
	int valueToSearch = 13;
	printf("\n%d\n", search(arr, 0, len - 1, valueToSearch));

	return 0;
}
